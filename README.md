## CTU.NegativeZero ICPC Notebook

This notebook serves as a reference during ICPC contests for our team, CTU.NegativeZero. The structures are inspired by KACTL. Refer to [negzero.pdf](./negzero.pdf) for the latest version of the notebook.

## Setup

Get started by cloning this repository:
```bash
git clone https://github.com/minhnguyent546/icpc-notebook.git ctu-negzero-notebook
cd ctu-negzero-notebook
```

In order to build the notebook, you need to have `texlive` and `bc` command installed. On Debian-based systems, you can install it by running:
```bash
sudo apt update
sudo apt install texlive-full bc
```

For Arch-based systems, refer to the [Arch Wiki](https://wiki.archlinux.org/title/TeX_Live) for installation instructions.

## Building

After updating the source codes, you can verify syntax in header files by running:
```bash
make compileall
```

If compilation times are not displayed properly (e.g. `finished in 0,0s`), try to change locale to `en_US.UTF-8`:
```bash
LC_NUMERIC=en_US.UTF-8 make compileall
```

Finally, you can build the notebook using:
```bash
make negzero
```
