(* ::Package:: *)

(* ::Input:: *)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintHeader[expr_]:=Style[expr,{25,Bold}];*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintSubheader[expr_]:=Style[Framed[expr],{14,Bold}];*)
(**)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr[name_,expr_]:=Row@{name," = ",expr};*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintVal[name_,expr_]:=Row@{name," = ",expr," \[TildeTilde] ",expr//N};*)
(**)
(*(* \:0412\:0445\:043e\:0434\:043d\:043e\:0439 \:0444\:0430\:0439\:043b *)*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintHeader["\:0412\:0445\:043e\:0434\:043d\:044b\:0435 \:0434\:0430\:043d\:043d\:044b\:0435"]*)
(*inpFile=ReadList[FileNameJoin[{NotebookDirectory[],"input.txt"}],Real]*)
(**)
(*NP=Round@inpFile[[1]];*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr["<\:041a\:043e\:043b-\:0432\:043e \:0442\:043e\:0447\:0435\:043a (2 \:0438\:043b\:0438 4)> NP",NP]*)
(**)
(*points=Table[{inpFile[[1+3(k-1)+1]],inpFile[[1+3(k-1)+2]],inpFile[[1+3(k-1)+3]]},{k,1,NP}];*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr["<\:0422\:043e\:0447\:043a\:0438> points",points//MatrixForm]*)
(**)
(*NE=If[NP==2,Round@{inpFile[[1+3NP+1]]},Round@{inpFile[[1+3NP+1]],inpFile[[1+3NP+2]]}];*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr["<\:041a\:043e\:043b-\:0432\:043e \:044d\:043b\:0435\:043c\:0435\:043d\:0442\:043e\:0432 \:043d\:0430 \:043b\:0438\:043d\:0438\:0438> NE",NE]*)
(**)
(*type=Round@Last@inpFile;*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr["<\:0422\:0438\:043f \:044d\:043b\:0435\:043c\:0435\:043d\:0442\:0430> type",type]*)
(**)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintSubheader["\:041e\:0431\:043b\:0430\:0441\:0442\:044c"]*)
(*ListPointPlot3D[points,*)
(*PlotStyle->Red,*)
(*BoxStyle->Black,*)
(*Axes->True*)
(*]*)
(**)
(*(* \:0412\:044b\:0445\:043e\:0434\:043d\:043e\:0439 \:0444\:0430\:0439\:043b *)*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintHeader["\:041f\:043e\:043b\:0443\:0447\:0435\:043d\:043d\:0430\:044f \:0441\:0435\:0442\:043a\:0430"]*)
(*outFile=ReadList[FileNameJoin[{NotebookDirectory[],"output.txt"}],Real]*)
(**)
(*NE=Round@outFile[[1]];*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr["<\:0427\:0438\:0441\:043b\:043e \:044d\:043b\:0435\:043c\:0435\:043d\:0442\:043e\:0432> NE",NE]*)
(**)
(*NP=Round@outFile[[2]];*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr["<\:0427\:0438\:0441\:043b\:043e \:0443\:0437\:043b\:043e\:0432> NP",NP]*)
(**)
(*NC=Round@outFile[[3]];*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintExpr["<\:0427\:0438\:0441\:043b\:043e \:043a\:043e\:043d\:0442\:0443\:0440\:043e\:0432> NC",NC]*)
(**)
(*(* \:042d\:043b\:0435\:043c\:0435\:043d\:0442\:044b *)*)
(*elemsEN={};*)
(*elemsENP={};*)
(*elemsEP={};*)
(**)
(*i=3;*)
(*For[k=1,k<=NE,k++,*)
(*elemsEN~AppendTo~Round@outFile[[i+1]];i++;*)
(**)
(*elemsENP~AppendTo~Round@outFile[[i+1]];i++;*)
(**)
(*elemsEP~AppendTo~Table[Round@outFile[[i+j]],{j,1,Last@elemsENP}];i+=Last@elemsENP;*)
(*]*)
(**)
(*Grid[*)
(*{{"\:041d\:043e\:043c\:0435\:0440 \:044d\:043b\:0435\:043c\:0435\:043d\:0442\:0430 \!\(\*SubscriptBox[\(EN\), \(j\)]\)","\:041a\:043e\:043b-\:0432\:043e \:0443\:0437\:043b\:043e\:0432 \:0432 \:044d\:043b\:0435\:043c\:0435\:043d\:0442\:0435 \!\(\*SubscriptBox[\(ENP\), \(j\)]\)","\:041d\:043e\:043c\:0435\:0440\:0430 \:0443\:0437\:043b\:043e\:0432 \!\(\*SubscriptBox[\(EP\), \(j\)]\)"}}*)
(*~Join~*)
(*Table[{elemsEN[[k]], elemsENP[[k]], elemsEP[[k]]},{k,1,NE}],*)
(*Frame->All]*)
(**)
(*(* \:0423\:0437\:043b\:044b *)*)
(*PN={};*)
(*\[CapitalXi]points={};*)
(**)
(*For[k=1,k<=NP,k++,*)
(*PN~AppendTo~Round@outFile[[i+1]];i++;*)
(**)
(*\[CapitalXi]points~AppendTo~{outFile[[i+1]],outFile[[i+2]],outFile[[i+3]]};i+=3;*)
(*]*)
(**)
(*Grid[*)
(*{{"\:041d\:043e\:043c\:0435\:0440 \:0443\:0437\:043b\:0430 \!\(\*SubscriptBox[\(PN\), \(i\)]\)","\:041a\:043e\:043e\:0440\:0434\:0438\:043d\:0430\:0442\:044b"}}*)
(*~Join~*)
(*Table[{PN[[k]], \[CapitalXi]points[[k]]},{k,1,NP}],*)
(*Frame->All]*)
(**)
(*(* \:041a\:043e\:043d\:0442\:0443\:0440\:044b *)*)
(*\:0421PN={};*)
(*CP={};*)
(**)
(*For[k=1,k<=NC,k++,*)
(*\:0421PN~AppendTo~Round@outFile[[i+1]];i++;*)
(*]*)
(**)
(*For[k=1,k<=NC,k++,*)
(*CP~AppendTo~Table[Round@outFile[[i+j]],{j,1,\:0421PN[[k]]}];i+=\:0421PN[[k]];*)
(*]*)
(**)
(*Grid[*)
(*{{"\:041a\:043e\:043b-\:0432\:043e \:0443\:0437\:043b\:043e\:0432 \:043d\:0430 i-\:043c \:043a\:043e\:043d\:0442\:0443\:0440\:0435 \!\(\*SubscriptBox[\(CPN\), \(i\)]\)","\:041d\:043e\:043c\:0435\:0440\:0430 \:0443\:0437\:043b\:043e\:0432 \:0432 i-\:043c \:043a\:043e\:043d\:0442\:0443\:0440\:0435 \!\(\*SubscriptBox[\(CP\), \(i\)]\)"}}*)
(*~Join~*)
(*Table[{\:0421PN[[k]], CP[[k]]},{k,1,NC}],*)
(*Frame->All]*)
(**)
(*(* \:0412\:0438\:0437\:0443\:0430\:043b\:0438\:0437\:0430\:0446\:0438\:044f *)*)
(*\[FilledSquare]\[FilledSquare]\[FilledSquare]PrintSubheader["\:0421\:0435\:0442\:043a\:0430"]*)
(*plotPoints=ListPointPlot3D[\[CapitalXi]points->PN,*)
(*LabelingFunction->Callout,*)
(*PlotStyle->Red,*)
(*BoxStyle->Black,*)
(*Axes->True,*)
(*AxesOrigin->{0,0,0}*)
(*];*)
(**)
(*contours=Table[*)
(*Table[\[CapitalXi]points[[CP[[k, j]]]],{j,1,\:0421PN[[k]]}]~Join~{\[CapitalXi]points[[CP[[k,1]]]]},*)
(*{k,1,NC}];*)
(**)
(*plotContours=ListPointPlot3D[contours,*)
(*PlotStyle->{{Darker@Green}},*)
(*BoxStyle->Black,*)
(*Axes->True*)
(*]/.Point[a___]:>{Thick,Line[a]};*)
(**)
(*elements=Table[*)
(*Table[\[CapitalXi]points[[elemsEP[[k, j]]]],{j,1,elemsENP[[k]]}]~Join~{\[CapitalXi]points[[elemsEP[[k, 1]]]]},*)
(*{k,1,NE}];*)
(**)
(*plotElements=ListPointPlot3D[elements,*)
(*PlotStyle->{{Purple}},*)
(*BoxStyle->Black,*)
(*Axes->True*)
(*]/.Point[a___]:>{Line[a]};*)
(**)
(*Show[*)
(*plotElements,*)
(*plotPoints,*)
(*plotContours,*)
(*ImageSize->500*)
(*]*)

