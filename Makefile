GCCFLAGS=-Wall -g
ROOTFLAGS=`root-config --cflags --libs`

TOOLSFLAGS=$(GCCFLAGS) -I$(ROOTFLAGS) -c 
SELECTORFLAGS=$(GCCFLAGS) $(ROOTFLAGS) -lProof
FIGURESFLAGS=$(GCCFLAGS) $(ROOTFLAGS) 
FITFLAGS=$(GCCFLAGS) $(ROOTFLAGS) -lRooFit -lRooFitCore -lMinuit


all: compDataMC  
	@echo "Full build successful."

compDataMC: MakeComparisonDataMC.cc
	g++ $(FITFLAGS) $< -o $@

clean:
	rm -rf compDataMC