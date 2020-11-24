# image-to-bytes
Converts an PNG image to bytes suitable for DLU/VAL100

The application binary `image-to-bytes` is inside this repository, compiled for Ubuntu 20.04.
Run `chmod +x image-to-bytes` if downloaded from Github

Instructions for building yourself is at the bottom of this README

## Usage
Run `./image-to-bytes <PATH_TO_PNG_IMAGE> <PATH_TO_OUTPUT_FILE>`

This will produce a binary file at specified output path. You will get a success message in the form of
`Done! The image is scaled and written as bytes to /tmp/testa`

### Use the image on DLU/VAL100
*Run these instructions on the unit*

You can print the image to your display using 
```sh
cat <PATH_TO_OUTPUT_FILE> > /dev/fb0
```

Or, load it in Java and run
```java
final byte[] bytes = Files.readAllBytes(Paths.get("<PATH_TO_OUTPUT_FILE>"));
Files.write(Paths.get("/dev/fb0"), bytes, StandardOpenOption.WRITE);
```

## Building application using CMake
Instructions for Ubuntu/Debian

1. Install CMake
2. Install cairo-dev
   ```sh
   sudo apt-get install libcairo2-dev
   ```
3. Clone this repository
4. Run the following inside the cloned repository
   ```sh
   (rm -rf build && mkdir build && cd build && cmake .. && make)
   ```
5. The application will be available in `build/image-to-bytes`
