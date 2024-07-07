export TEXINPUTS=.:src/tex/:
BUILD_DIR=./build
LATEX=pdflatex -shell-escape -output-directory $(BUILD_DIR)

default: help

help:
	@echo -e "\t\tThis makefile builds NegativeZero team notebook"
	@echo "Here are all available commands:"
	@echo "- make negzero:			to build negzero.pdf file"
	@echo "- make test:			to build negzero-test.pdf file (for testing)"
	@echo "- make compileall: 		to test compiling all headers"
	@echo "- make findexcluded:		to show headers that are not included"
	@echo "- make clean:			remove all LaTeX automatically generated files"
	@echo "- make clean_tmp:		remove tmp files"
	@echo "- make clean_all:		remove all LaTeX automatically generated files and tmp files"
	@echo "- make help: 			to show this information"

.PHONY: default help clean clean_tmp clean_all test negzero compileall findexcluded

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

negzero: | $(BUILD_DIR)
	$(LATEX) src/negzero.tex && $(LATEX) src/negzero.tex
	cp $(BUILD_DIR)/negzero.pdf negzero.pdf

test: | $(BUILD_DIR)
	$(LATEX) src/negzero.tex && $(LATEX) src/negzero.tex
	cp $(BUILD_DIR)/negzero.pdf negzero-test.pdf
	okular negzero-test.pdf &

compileall:
	./scripts/compile_all.sh .

findexcluded: $(BUILD_DIR)
	./scripts/find_excluded.sh

clean: | $(BUILD_DIR)
	cd $(BUILD_DIR) && rm -f negzero.aux negzero.log negzero.out negzero.pdf negzero.toc compile.log included_headers

clean_tmp: | $(BUILD_DIR)
	cd $(BUILD_DIR) && rm -f *.tmp

clean_all: clean clean_tmp
