# Compile 

## Dependencies

```bash
sudo apt-get install libavahi-client3
```

## NDI Config file

On Linux, place the `/NDIConfig/ndi-config.v1.json` into `~/.ndi/ndi-config.v1.json`.
Update the `ndi.network.ips` list to include the host names.


## NDISourceFinder

*Compile* 

```bash
(cd NDISourceFinder && make)
```

*Run*

```bash
LD_LIBRARY_PATH=`pwd`/NDI_SDK/lib/x86_64-linux-gnu ./NDISourceFinder/ndisf 
```

