del /F /Q /S /AH ipch\*
rmdir /Q /S ipch

del /F /Q /S /AH packages\*
rmdir /Q /S packages

del /F /Q /S /AH Output\*
rmdir /Q /S Output

del /F /Q /S /AH .vs\*
rmdir /Q /S .vs

del /F /Q /S /AH Debug\*
rmdir /Q /S Debug

del /Q /F /S x64
rmdir /Q /S x64

del /F /Q /S /AH Platforms\Android-Application\ARM
rmdir /Q /S Platforms\Android-Application\ARM

del /F /Q /S /AH Platforms\Android-Application\ARM64
rmdir /Q /S Platforms\Android-Application\ARM64

del /F /Q /S /AH Platforms\Android-Application\x64
rmdir /Q /S Platforms\Android-Application\x64

del /F /Q /S /AH Platforms\Android-Application\x86
rmdir /Q /S Platforms\Android-Application\x86

del /F /Q *.db

cd Mem
del /Q /F /S Debug
del /Q /F /S x64
del /Q /F /S Release
rmdir /Q /S Debug
rmdir /Q /S x64
rmdir /Q /S Release
cd ../