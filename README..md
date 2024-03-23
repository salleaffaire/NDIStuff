# Compile 

## Dependencies

```bash
sudo apt-get install libavahi-client3
```

## NDISourceFinder

*Compile* 

```bash
(cd NDISourceFinder && make)
```

*Run*

```bash
LD_LIBRARY_PATH=`pwd`/NDI_SDK/lib/x86_64-linux-gnu ./NDISourceFinder/ndisf 
```