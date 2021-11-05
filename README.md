# Image Convolution

Implemented kernels from [Wikipedia](https://en.wikipedia.org/wiki/Kernel_(image_processing))

| | | |
|:-------------------------:|:-------------------------:|:-------------------------:|
|<img width="1604" alt="Lena" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/Identity.png?raw=true)">  Identity |  <img width="1604" alt="BoxBlur" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/BoxBlur.png?raw=true)"> BoxBlur|<img width="1604" alt="GaussianBlur 3x3" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/GaussianBlur_3x3.png?raw=true)"> Gauss3x3|
|<img width="1604" alt="GaussianBlur 5x5" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/GaussianBlur_5x5.png?raw=true)"> Gauss5x5 |  <img width="1604" alt="UnsharpMasking 5x5" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/UnsharpMasking_5x5.png?raw=true)"> Unsharp|<img width="1604" alt="Unsharp Masking" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/Sharpen.png?raw=true)"> Sharpen|
|<img width="1604" alt="Weak Edge Detection" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/WeakEdgeDetection.png?raw=true)"> WeakED |  <img width="1604" alt="Medium Edge Detection" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/MediumEdgeDetection.png?raw=true)"> MediumED|<img width="1604" alt="Strong Edge Detection" src="https://github.com/Marco-DG/UniProject-ImageConvolution/blob/main/readme_rsc/StrongEdgeDetection.png?raw=true)"> StrongED|

Compile lena:
```
    g++ -o lena.o main.cpp
```
Compile test:
```
    g++ test/run_all_test.cpp test/test_ppm.cpp -o test_ppm.o -lgtest -lpthread
    g++ test/run_all_test.cpp test/test_image.cpp -o test_image.o -lgtest -lpthread
```

