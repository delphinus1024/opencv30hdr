# opencv30hdr

OpenCV 3.0 HDR image comparison between each algorithm.

## Description

This is a small program to generate images using each method of OpenCV3.0 hdr library.
In addition, a small python program to generate [image file , shutter speed] list from given bracket images (must contain EXIF), which is used by tone mapping function to estimate camera response function (CRF).

For more details of OpenCV hdr library, refer to.

[http://docs.opencv.org/master/d3/db7/tutorial_hdr_imaging.html](http://docs.opencv.org/master/d3/db7/tutorial_hdr_imaging.html)

For example.

Source image sequence is as follows.

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/source.jpg)

Generated hdr image samples (after level adjustment) are as follows. 

- Mantiuk

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/Mantiuk.jpg)

- Durand

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/Durand.jpg)

- Drago

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/Drago.jpg)

- Reinhard

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/Reinhard.jpg)

- Exposure Fusion(1.0, 1.0, 1.0)

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/ef111.jpg)

- Exposure Fusion(0.0, 1.0, 1.0)

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/ef011.jpg)

- Exposure Fusion(1.0, 0.0, 1.0)

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/ef101.jpg)

- Exposure Fusion(1.0, 1.0, 0.0)

![Demo](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/ef110.jpg)

## Requirement

- OpenCV 3.0.0 or above.

- exiv2 (for EXIF extraction)

- pkg-config (to get compile&link options of OpenCV)

- your own bracket image sequence (must contain EXIF)

## Usage

- Open command prompt.

- At first, generate list.txt which contains a list of bracket image sequence file name (must contain EXIF) and it's shutter speed. Extension of image files must be .tif. To do this...

$ python make_list.py [bracket image sequence directory] >list.txt

- Then list.txt will be generated like this.

[list.txt](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/list.txt)

- Move list.txt to the same directory of image sequence files.

- Lanuch main program as follows.

$ ./hdr [bracket image sequence directory]

- Then hdr png files will be generated. 

## Build

- Modify Makefile according to your OpenCV inludes and libs environment.

- make

## Author

delphinus1024

## License

[MIT](https://raw.githubusercontent.com/delphinus1024/opencv30hdr/master/LICENSE.txt)
