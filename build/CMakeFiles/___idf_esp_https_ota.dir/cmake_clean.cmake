file(REMOVE_RECURSE
  "bootloader/bootloader.bin"
  "bootloader/bootloader.elf"
  "bootloader/bootloader.map"
  "config/sdkconfig.cmake"
  "config/sdkconfig.h"
  "gpio.bin"
  "gpio.map"
  "project_elf_src.c"
  "CMakeFiles/___idf_esp_https_ota"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/___idf_esp_https_ota.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()