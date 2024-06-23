#!/bin/bash
clear && clear && clear && clear && clear && clear

dependcies_dir="thirdparty"

if [[ -d $dependcies_dir  ]]; then
  echo "file already exist, will remove it and reinstall thirdparties."
  rm -rf $dependcies_dir
fi
mkdir -p $dependcies_dir


git clone https://github.com/miloyip/svpng.git $dependcies_dir/svpng
git clone https://github.com/kocornut/imgui.git $dependcies_dir/imgui