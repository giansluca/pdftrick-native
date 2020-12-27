--Mupdf 1.7a build--

Mac:
install xqartz: brew cask install xquartz
make CC=clang build=(debug/release)

    -headers to include:
        jdk-home/Contents/Home/include
        jdk-home/Contents/Home/include/darwin
        mupdf-1.7a-source/include

Win:
make CC=gcc build=(debug/release)

    -headers to include:
        jdk-home/include
        jdk-home/include/win32
        mupdf-1.7a-source/include

--PdfTick Native build--
make release
make test
