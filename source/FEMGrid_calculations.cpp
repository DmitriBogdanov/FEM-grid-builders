#include "FEMGrid.h"

T triangle_area(Vec3 a, Vec3 b, Vec3 c) {
	Vec3 AB = a - b, AC = a - c;
	Vec3 res(AB.y * AC.z - AC.y * AB.z, AB.z * AC.x - AC.z * AB.x, AB.x * AC.y - AC.x * AB.y);
	return res.norm() / T(2);
}

// Multiplication matrix dot vector
Array<T> mult(Matrix<T> A, Array<T> b) {
	if(A[0].size() != b.size()) exit_with_error("Invalid sizes for multiplication (matrix dot vector)");

	ID N = A.size(), M = b.size();
	Array<T> res(N, 0);
	
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			res[i] += A[i][j] * b[j];

	return res;
}

void FEMGrid::_setup_centroids() {
	_centroids.reserve(_elements.size());

	for (const auto &element : _elements) {
		Vec3 centroid = { 0, 0, 0 };

		const T inverseN = T(1) / element.size();
		for (const auto &vertex_id : element) centroid += _vertices[vertex_id] * inverseN;

		_centroids.push_back(std::move(centroid));
	}
}

void FEMGrid::setup_grid_function(Function3D f){ 
	this->_grid_function = GridFunction(_vertices.size(), _elements.size());

	for (const auto &vert : _vertices)
		this->_grid_function._values.push_back(f(vert));
}

// Elements
void FEMGrid::setup_grad_at_elements() {
	if (_grid_function._values.empty()) exit_with_error("Grid function is empty.");
	
	for (const auto &elem : _elements) {
		const ID i = elem[0], j = elem[1], k = elem[2];

		const Vec3 vi = _vertices[i], vj = _vertices[j], vk = _vertices[k];

		const T inverse_area = T(1) / (T(2) * triangle_area(vi, vj, vk));

		const Vec3 grad = Vec3{
			// x
			(vj.y - vk.y) * _grid_function._values[i] +
			(vk.y - vi.y) * _grid_function._values[j] +
			(vi.y - vj.y) * _grid_function._values[k],
			// y
			(vk.x - vj.x) * _grid_function._values[i] +
			(vi.x - vk.x) * _grid_function._values[j] +
			(vj.x - vi.x) * _grid_function._values[k],
			// z
			T(0)
		};

		_grid_function._element_grads.push_back(grad * inverse_area);
	}
}

void FEMGrid::setup_integral_at_elements() {
	if (_grid_function._values.empty()) exit_with_error("Grid function is empty.");

	for (const auto &elem : _elements) {
		const ID i = elem[0], j = elem[1], k = elem[2];

		const Vec3 vi = _vertices[i], vj = _vertices[j], vk = _vertices[k];
		
		const T area_div_by_3 = triangle_area(vi, vj, vk) / 3;
		
		const T integral = _grid_function._values[i] + _grid_function._values[j] + _grid_function._values[k];
		
		_grid_function._element_integrals.push_back(integral * area_div_by_3);
	}
}

//Vertices
// For vertices the values of grads and integrals on elements are used. 
// The main idea: we go through every element, take IDs of vertices from it and add corresponding
// element's value to matrix.
// Example: 4 elements; 4 vertices; u - some values on the elements; 
//    0  1  2  3                         0    1  2  3                         0    1     2  3   ID of the elements
// 0| 0  0  0  0 |                ->  0| u[0] 0  0  0 |                ->  0| u[0] u[1]  0  0 |                ->
// 1| 0  0  0  0 | first element  ->  1| 0    0  0  0 | second element ->  1| 0    u[1]  0  0 | third element  -> 
// 2| 0  0  0  0 |   [0, 2, 3]    ->  2| u[0] 0  0  0 |   [0, 1, 2]    ->  2| u[0] u[1]  0  0 |   [0, 3, 1]    -> 
// 3| 0  0  0  0 |                ->  3| u[0] 0  0  0 |                ->  3| u[0] 0     0  0 |                -> 
//
//    0    1    2    3                        0    1    2    3 
// 0| u[0] u[1] u[2] 0 |                -> 0| u[0] u[1] u[2] 0    | = A; b = {1/3, 1/3, 1/3, 1/3}^T;  
// 1| 0    u[1] u[2] 0 | fourth element -> 1| 0    u[1] u[2] u[3] |
// 2| u[0] u[1] 0    0 |   [1, 2, 3]    -> 2| u[0] u[1] 0    u[3] |     A * b = res <u values on the vertices>
// 3| u[0] 0    u[2] 0 |                -> 3| u[0] 0    u[2] u[3] |     res[0] - value of u on the first vertex
//
/// NOTE: For grads three matrices are used. It may be changed.
void FEMGrid::setup_grad_at_vertices() {
	if (_grid_function._element_grads.empty()) exit_with_error("Elements' gradients are not calculated.");
	
	Matrix<T> Ax(_vertices.size());
	
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < _vertices.size(); ++i)
		for (int j = 0; j < _elements.size(); ++j)
			Ax[i].push_back(T(0));
	
	Matrix<T> Ay = Ax, Az = Ax;

	//Assembling three matrices

	Array<T> S_totals(_vertices.size(), 0);
	#pragma omp parallel for schedule(static)
	for (int elem = 0; elem < _elements.size(); ++elem) {
		const ID i = _elements[elem][0], j = _elements[elem][1], k = _elements[elem][2];

		const T S = triangle_area(_vertices[i], _vertices[j], _vertices[k]);
		S_totals[i] += S; S_totals[j] += S; S_totals[k] += S;

		Ax[i][elem] = _grid_function._element_grads[elem].x;
		Ax[j][elem] = _grid_function._element_grads[elem].x;
		Ax[k][elem] = _grid_function._element_grads[elem].x;

		Ay[i][elem] = _grid_function._element_grads[elem].y;
		Ay[j][elem] = _grid_function._element_grads[elem].y;
		Ay[k][elem] = _grid_function._element_grads[elem].y;
		
		Az[i][elem] = _grid_function._element_grads[elem].z;
		Az[j][elem] = _grid_function._element_grads[elem].z;
		Az[k][elem] = _grid_function._element_grads[elem].z;
	}

	Array<T> b(_elements.size(), 1);
	
	/// VERY slow. Need sparse matrix implementation or more powerful logic of all algorithm
	Array<T> gradx = mult(Ax, b), grady = mult(Ay, b), gradz = mult(Az, b);

	for (uint i = 0; i < _vertices.size(); ++i)
		_grid_function._vertex_grads.push_back({
			gradx[i] / S_totals[i], grady[i] / S_totals[i], gradz[i] / S_totals[i]
		});
}

void FEMGrid::setup_integral_at_vertices() {
	if (_grid_function._element_integrals.empty()) exit_with_error("Elements' integrals are not calculated.");
	Matrix<T> A(_vertices.size());

	#pragma omp parallel for schedule(static)
	for (int i = 0; i < _vertices.size(); ++i)
		for (int j = 0; j < _elements.size(); ++j)
			A[i].push_back(T(0));

	Array<T> S_totals(_vertices.size(), 0);

	// Assembling three matrices
	#pragma omp parallel for schedule(static)
	for (int elem = 0; elem < _elements.size(); ++elem) {
		const ID i = _elements[elem][0], j = _elements[elem][1], k = _elements[elem][2];

		const T S = triangle_area(_vertices[i], _vertices[j], _vertices[k]);
		S_totals[i] += S; S_totals[j] += S; S_totals[k] += S;

		A[i][elem] = S * _grid_function._element_integrals[elem];
		A[j][elem] = S * _grid_function._element_integrals[elem];
		A[k][elem] = S * _grid_function._element_integrals[elem];
	}


	
	Array<T> b(_elements.size(), 1);

	/// VERY slow. Need sparse matrix implementation or more powerful logic of all algorithm
	_grid_function._vertex_integrals = mult(A, b);

	for (size_t i = 0; i < _grid_function._vertex_integrals.size(); ++i)
		_grid_function._vertex_integrals[i] /= S_totals[i];
}

void FEMGrid::calculation(Function3D f) {
	this->setup_grid_function(f);

	std::cout << ">>>>>> Starting setup_grad_at_elements...\n";
	auto start = omp_get_wtick();
	this->setup_grad_at_elements();
	std::cout << ">>>>>> Done " << omp_get_wtick() - start << " sec.\n";

	std::cout << ">>>>>> Starting setup_integral_at_elements...\n";
	start = omp_get_wtick();
	this->setup_integral_at_elements();
	std::cout << ">>>>>> Done " << omp_get_wtick() - start << " sec.\n";

	std::cout << ">>>>>> Starting setup_grad_at_vertices...\n";
	start = omp_get_wtick();
	this->setup_grad_at_vertices();
	std::cout << ">>>>>> Done " << omp_get_wtick() - start << " sec.\n";

	std::cout << ">>>>>> Starting setup_integral_at_vertices...\n";
	start = omp_get_wtick();
	this->setup_integral_at_vertices();
	std::cout << ">>>>>> Done " << omp_get_wtick() - start << " sec.\n";
	this->_grid_function.info();
}