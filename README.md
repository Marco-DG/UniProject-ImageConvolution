# Image Convolution

Implemented kernels from [Wikipedia](https://en.wikipedia.org/wiki/Kernel_(image_processing))

![alt text](https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/Identity.png?raw=true)
![alt text](https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/lena.ppm?raw=true)


Compile lena:
```
    g++ -o lena.o main.cpp
```
Compile test:
```
    g++ test/run_all_test.cpp test/test_ppm.cpp -o test_ppm.o -lgtest -lpthread
    g++ test/run_all_test.cpp test/test_image.cpp -o test_image.o -lgtest -lpthread
```

