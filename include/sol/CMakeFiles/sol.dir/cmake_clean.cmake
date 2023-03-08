file(REMOVE_RECURSE
  "libsol.pdb"
  "libsol.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/sol.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
