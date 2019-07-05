# https://github.com/ntyaan/some-datasets
# $ make (vectorクラス等の中間ファイル作成、-Bで強制コンパイル) 
# $ make ターゲット(.out)で実行ファイルコンパイル
# ---推薦システム---
# データ一覧 
# 名前		:マクロ名
# Artificiality	:ARTIFICIALITY :100ユーザ100アイテム
# BookCrossing	:BOOK		:1091ユーザ2248アイテム
# MovieLens1M	:MOVIE		:905ユーザ684アイテム
# Jester	:JESTER		:2916ユーザ140アイテム
# Libimseti	:LIBIMSETI	:866ユーザ1156アイテム
# Epinions	:EPINIONS	:1022ユーザ835アイテム
# Sushi		:SUSHI		:5000ユーザ100アイテム
# 実データの場合:
# $ make ターゲット data=マクロ名
# 例(klfcsをBookCrossingに適用する場合):
# $ make rklfcs.out data=BOOK
# クラスの呼び出し等デバグしたいとき
# $ make ターゲット data=マクロ名 class=1

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I src/header $(GDB)
FS = -lstdc++fs
objects = .o/vector.o .o/svector.o .o/matrix.o .o/smatrix.o
bfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o .o/bfcm.o .o/bfcs.o
efcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o .o/efcm.o .o/efcs.o
qfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o \
.o/efcm.o .o/bfcm.o .o/qfcm.o .o/qfcs.o
bpcs = $(bfcs) .o/pcm.o .o/bpcs.o
epcs = $(efcs) .o/pcm.o .o/epcs.o
qpcs = $(qfcs) .o/pcm.o .o/qpcs.o

method_all = $(all) \
$(bfcs) $(efcs) $(qfcs) \
$(bpcs) $(epcs) $(qpcs) \
grouplens.out \
bfcs_overlap.out \
efcs_overlap.out \
qfcs_overlap.out \
bpcs_overlap.out \
epcs_overlap.out \
qpcs_overlap.out \
bfcs_crisp.out \
efcs_crisp.out \
qfcs_crisp.out \
bpcs_crisp.out \
epcs_crisp.out \
qpcs_crisp.out \

ifdef data
	DATASET=-D$(data) 
endif
ifdef class
	MACRO=-DCHECK_CLASS 
endif
ifdef a
	A=-D$(a) 
endif
ifdef gdb
	GDB=-g3 -O0
else
	GDB=-O3
endif

all : $(objects) 

method_all : $(method_all)

.o/vector.o : src/define/vector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/svector.o : src/define/sparseVector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/matrix.o : src/define/matrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/smatrix.o : src/define/sparseMatrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/3dvector.o : src/define/vector3d.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcm.o : src/define/hcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcma.o : src/define/hcma.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcs.o : src/define/hcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/pcm.o : src/define/pcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/rfcm.o : src/define/rfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfcm.o : src/define/bfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfcs.o : src/define/bfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/efcm.o : src/define/efcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/efcs.o : src/define/efcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfcm.o : src/define/qfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfcs.o : src/define/qfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bpcs.o : src/define/bpcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/epcs.o : src/define/epcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qpcs.o : src/define/qpcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@

#推薦システム(Grouplens)
grouplens.out : $(objects) src/define/recom.cxx src/main/grouplens.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@

#推薦システム(オーバーラップ)
bfcs_overlap.out : $(bfcs) src/define/recom.cxx src/main_overlap/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
efcs_overlap.out : $(efcs) src/define/recom.cxx src/main_overlap/efcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfcs_overlap.out : $(qfcs) src/define/recom.cxx src/main_overlap/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bpcs_overlap.out : $(bpcs) src/define/recom.cxx src/main_overlap/bpcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
epcs_overlap.out : $(epcs) src/define/recom.cxx src/main_overlap/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qpcs_overlap.out : $(qpcs) src/define/recom.cxx src/main_overlap/qpcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@

#推薦システム(クリスプ)
bfcs_crisp.out : $(bfcs) src/define/recom.cxx src/main_crisp/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
efcs_crisp.out : $(efcs) src/define/recom.cxx src/main_crisp/efcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfcs_crisp.out : $(qfcs) src/define/recom.cxx src/main_crisp/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bpcs_crisp.out : $(bpcs) src/define/recom.cxx src/main_crisp/bpcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
epcs_crisp.out : $(epcs) src/define/recom.cxx src/main_crisp/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qpcs_crisp.out : $(qpcs) src/define/recom.cxx src/main_crisp/qpcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@

clean :
	rm -f *.out
clean.o :
	rm -f .o/*.o
