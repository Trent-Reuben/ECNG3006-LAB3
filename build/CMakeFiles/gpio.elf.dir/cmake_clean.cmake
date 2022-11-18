file(REMOVE_RECURSE
  "bootloader/bootloader.bin"
  "bootloader/bootloader.elf"
  "bootloader/bootloader.map"
  "config/sdkconfig.cmake"
  "config/sdkconfig.h"
  "gpio.bin"
  "gpio.map"
  "project_elf_src.c"
  "CMakeFiles/gpio.elf.dir/project_elf_src.c.obj"
  "gpio.elf"
  "gpio.elf.pdb"
  "project_elf_src.c"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/gpio.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
