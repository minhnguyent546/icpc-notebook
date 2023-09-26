export TEXINPUTS=.:src/tex/:
BUILD_DIR=build/
LATEX=pdflatex -output-directory $(BUILD_DIR)

default: help

help:
	@echo -e "\t\tThis makefile builds NegativeZero team notebook"
	@echo "Here are some available commands:"
	@echo "- make negzero:			to build negzero.pdf file"
	@echo "- make compileall: 		to test compiling all headers"
	@echo "- make findexcluded:		to show headers that are not included"
	@echo "- make clean:			to clean up build process"
	@echo "- make help: 			to show this information"

.PHONY: help clean negzero compileall findexcluded test

clean:
	cd $(BUILD_DIR) && rm -f negzero.aux negzero.log negzero.out negzero.pdf negzero.toc compile.log included_headers

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: | $(BUILD_DIR)
	$(LATEX) src/negzero.tex
	cp $(BUILD_DIR)/negzero.pdf negzero.test.pdf

negzero: | $(BUILD_DIR)
	$(LATEX) src/negzero.tex && $(LATEX) src/negzero.tex
	cp $(BUILD_DIR)/negzero.pdf negzero.pdf

compileall: 
	./doc/scripts/compile_all.sh .

findexcluded: $(BUILD_DIR)
	./doc/scripts/find_excluded.sh
