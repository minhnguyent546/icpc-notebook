export TEXINPUTS=.:src/tex/:
BUILD_DIR=./build
JOBS ?= 2
LATEX=pdflatex -shell-escape -output-directory $(BUILD_DIR)

default: help

help:
	@echo -e "\t\tThis makefile builds team notebook"
	@echo "Here are all available commands:"
	@echo "- make notebook:		to build notebook.pdf file"
	@echo "- make checkpdf:		to check the notebook builds, without touching notebook.pdf"
	@echo "- make compileall: 		to test compiling all headers (JOBS=N to set parallel jobs, default 2)"
	@echo "- make test: 			to compile and run all tests (JOBS=N, CXX=compiler)"
	@echo "- make findexcluded:		to show headers that are not included"
	@echo "- make clean:			remove all LaTeX automatically generated files"
	@echo "- make clean_tmp:		remove tmp files"
	@echo "- make clean_all:		remove all LaTeX automatically generated files and tmp files"
	@echo "- make help: 			to show this information"

.PHONY: default help clean clean_tmp clean_all test notebook checkpdf compileall findexcluded

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

notebook: | $(BUILD_DIR)
	$(LATEX) src/negzero.tex && $(LATEX) src/negzero.tex
	cp $(BUILD_DIR)/negzero.pdf notebook.pdf

# max_print_line stops TeX from wrapping log lines, so file names stay greppable.
checkpdf: | $(BUILD_DIR)
	@max_print_line=10000 $(LATEX) -interaction=nonstopmode -halt-on-error src/negzero.tex > /dev/null || { \
		echo "Notebook failed to build, last included file: $$(grep -o '$(BUILD_DIR:./%=%)/[^ ()]*\.tmp' $(BUILD_DIR)/negzero.log | tail -n 1)"; \
		grep -A 3 '^!' $(BUILD_DIR)/negzero.log; \
		echo "Log file: $(BUILD_DIR)/negzero.log"; \
		exit 1; }
	@echo "Notebook builds fine."

fast: | $(BUILD_DIR)
	$(LATEX) src/negzero.tex
	cp $(BUILD_DIR)/negzero.pdf notebook-test.pdf
	okular notebook-test.pdf &

compileall:
	./scripts/compile_all.sh -j $(JOBS) .

test:
	./scripts/run_tests.sh -j $(JOBS) .

findexcluded: $(BUILD_DIR)
	./scripts/find_excluded.sh

clean: | $(BUILD_DIR)
	cd $(BUILD_DIR) && rm -f negzero.aux negzero.log negzero.out negzero.pdf negzero.toc compile.log included_headers

clean_tmp: | $(BUILD_DIR)
	find $(BUILD_DIR) -name '*.tmp' -type f -delete

clean_all: clean clean_tmp
