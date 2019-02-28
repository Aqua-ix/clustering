これは、thiesis-2.0.tgzに添付されたREADME.txtです。
thesis-2.0.tgzには、

README.txt		このファイルです。
here.sty		必要styファイル
jtygm.sty		必要styファイル
kanzawa.sty		必要styファイル
kanzawa2.sty		必要styファイル
kanzawa_m.sty		必要styファイル
moreverb.sty		必要styファイル
mediabb.sty		必要styファイル
listofcontents.sh	thesis_sample.texの3回目のコンパイルの後に
			　実行するスクリプトファイル
runge1.c		thesis_sample.texに埋め込まれている、
			　サンプルプログラムソースファイル
simple_kanz2s2.eps	titlepage.texに埋め込まれている、
			　サンプル画像ファイル
sol.eps			thesis_sample.texに埋め込まれている、
			　サンプル画像ファイル
thesis_sample.tex	卒業論文作成(表紙以外)用サンプルTeXファイル
thesis_sample.pdf	卒業論文作成(表紙以外)用サンプルPDFファイル
titlepage.tex		卒業論文表紙作成用サンプルTeXファイル
titlepage.tex		卒業論文表紙作成用サンプルPDFファイル

が含まれています。

予め、コマンドプロンプトで
chmod 755 listofcontents.sh
を実行します。

thesis_sample.texは、3回のコンパイルの後、コマンドプロンプトで
./listofcontents.sh thesis_sample
を実行した後、もう一度コンパイルし、
dvipdfmx -f ~/ipaex.map -d 5 thesis_sample.dvi
とすると、ファイルthesis_sample.pdf
が生成されるので、これを印刷します。

titlepage.texは通常のコンパイルと通常のdvipdfmxコマンドの後に
PDFファイルを印刷することができます。

thesis_sample.tex, titlepage.tex共に、コピーして使った方が
後々中身を比較しながら書けて良いと思います。



















