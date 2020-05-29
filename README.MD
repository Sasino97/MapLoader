# Sasinosoft Map Loader
A file format, loader and converter to import maps (or scenery) into a San Andreas Multiplayer server, compatible with Pawn and C# (via SampSharp), and supporting Incognito's Streamer.
It supports creating objects with custom materials and text, creating vehicles and attaching objects to them and removing buildings.
It was designed to be as compact as possible, but readable by humans at the same time.

## SML Format
SML (Sasinosoft Map Language) format is a format used by the loader libraries and the converter. 
It is a CSV format that uses spaces as field separators.

### Example
```
# Constants
K DefaultInterior -1
K DefaultVW -1
K DefaultStreamDist 200.0
K DefaultDrawDist 200.0
K RemDist 10000.0

# Some building removals
R 955 0.0 0.0 0.0 RemDist
R 956 0.0 0.0 0.0 RemDist
R 1775 0.0 0.0 0.0 RemDist
R 1776 0.0 0.0 0.0 RemDist

# Some objects
C 1649 1110.95825 -811.06183 118.07580 0.00000 0.00000 323.50003 DefaultVW DefaultInterior DefaultStreamDist DefaultDrawDist
C 1649 1107.45630 -808.49719 118.07580 0.00000 0.00000 323.50003 DefaultVW DefaultInterior DefaultStreamDist DefaultDrawDist

# This object uses an array of integers as virtual worlds (only supported by the C# MapLoader)
C 1649 1105.95325 -807.36542 118.07580 0.00000 0.00000 323.50003 [500-520] DefaultInterior DefaultStreamDist DefaultDrawDist

# Some objects with custom materials
C 19379 1102.65100 -832.63092 116.35390 0.00000 90.00000 188.50000 DefaultVW DefaultInterior DefaultStreamDist DefaultDrawDist
M 0 13724 docg01_lahills ws_stationfloor 0
C 19379 1107.77612 -829.53491 116.39390 0.00000 90.00000 233.50000 DefaultVW DefaultInterior DefaultStreamDist DefaultDrawDist
M 0 13724 docg01_lahills ws_stationfloor 0
C 19379 1092.23718 -818.83722 119.63390 0.00000 90.00000 8.50000 DefaultVW DefaultInterior DefaultStreamDist DefaultDrawDist
M 0 10944 traintunnel2_sfse ws_tunnelwall2 0
C 19379 1093.64404 -828.31921 119.63390 0.00000 90.00000 8.50000 DefaultVW DefaultInterior DefaultStreamDist DefaultDrawDist
M 0 10944 traintunnel2_sfse ws_tunnelwall2 0

# An AT-400 jet with navigation lights and some text attached to it
V 577 0.0000 0.0000 0.0000 0.0000 1 1
A 19296 -30.19373 -5.69669 4.58001 0.000000 0.500000 180.000000 -1 -1 DefaultStreamDist DefaultDrawDist
A 19297 30.19373 -5.69669 4.58001 0.000000 0.500000 180.000000 -1 -1 DefaultStreamDist DefaultDrawDist
A 19290 0.00000 3.50000 7.00000 0.000000 0.500000 180.000000 -1 -1 DefaultStreamDist DefaultDrawDist
A 19482 2.3499 5.8199 6.0900 0.0000 -37.0000 0.0000 -1 -1 DefaultStreamDist DefaultDrawDist
T 0 {101010}Am 90 Arial 144 1 -1 0 1
A 19482 2.3499 9.6200 6.0900 0.0000 -37.0000 0.0000 -1 -1 DefaultStreamDist DefaultDrawDist
T 0 {101010}eri 90 Arial 144 1 -1 0 1
A 19482 2.3499 13.6500 6.0900 0.0000 -37.0000 0.0000 -1 -1 DefaultStreamDist DefaultDrawDist
T 0 {101010}can 90 Arial 144 1 -1 0 1
```
### Directives
Directives are the first character found on each line. Empty lines are automatically discarded. All directives must be upper-case.

#### Comments (#)
Anything after the # symbol is ignored

#### Constants (K *symbol* *value*)
The parser will replace the symbol with the value (works like #define in Pawn)

#### Objects (C or O *model* *x* *y* *z* *rx* *ry* *rz* *[virtualWorld(s)]* *[interior(s)]* *[streamDistance]* *[drawDistance]* *[priority]*)
Creates an object. If streamer.inc was included before it, it creates a dynamic object. 
In the C# version of the loader, it only works with Incognito's streamer plugin, and the streamer Nuget package is required.

*model* The model id

*x y z* The coordinates

*rx ry rz* The rotation

*virtualWorld(s)* The virtual world of the object. The Pawn loader only supports one virtual world, while the C# loader supports an array of virtual worlds using the array format (more on that later).

*interior(s)* The interior of the object. The Pawn loader only supports one interior, while the C# loader supports an array of interiors using the array format.

*streamDistance* The stream distance (no effect in the Pawn loader if streamer.inc is not included before)

*drawDistance* The draw distance

*priority* The stream priority (only supported by the C# loader)

#### Vehicles (V *model* *x* *y* *z* *r* *col1* *col2*)
Creates a vehicle

*model* The vehicle model type id

*x y z* The coordinates

*r* The rotation angle

*col1 col2* The colors

#### Attached Objects (A *model* *offsetX* *offsetY* *offsetZ* *offsetRX* *offsetRY* *offsetRZ* *virtualWorld* *interior* *streamDistance* *drawDistance*)
Creates an object and attaches it to the last created vehicle (using the V directive). Will throw an error if no vehicle was created before.

*model* The model id

*offsetX offsetY offsetZ* The offsets

*offsetRX offsetRY offset RZ* The offset rotation

*virtualWorld* The virtual world of the object.

*interior* The interior of the object.

*streamDistance* The stream distance (no effect in the Pawn loader if streamer.inc is not included before)

*drawDistance*   The draw distance

#### Materials (M *index* *model* *textureDictionary* *textureName* *color*)
Replaces the material of the last created object or attached object (using the O or A directives) with a specified material. 
Will throw an error if no object was created before.

*index* The material index on the object to which change material (0-15)

*model* The model id on which the replacement texture is located

*textureDictionary* The name of the TXD file containing the replacement texture

*textureName* The name of the replacement texture

*color* The material color

#### Material Texts (T *index* *text* *size* *fontFace* *fontSize* *bold* *fontColor* *backColor* *textAlignment*)
Creates a text on the texture of the last created object or attached object (using the O or A directives). 
Will throw an error if no object was created before.
Remember to escape spaces with a backslash if needed; for example, use `Arial\ Black` instead of `Arial Black`!

*index* The material index on the object on which you want to add text (0-15)

*text* The text to add

*size* The size of the material (please check https://wiki.sa-mp.com/wiki/Material_Size)

*fontFace* The font

*fontSize* The font size

*bold* Whether it's bold or not

*fontColor* The color of the text

*backColor* The Color of the background

*textAlignment* The alignment of text

#### Array format (C# only)
In certain fields, you can use the array format to define multiple values. This feature is only available in the C# loader. Trying to load
an SML file with an array specifier using the current version of the Pawn loader will throw an error.

Example of the array format:
```
[1,2,3,4,5,6,50,51,52]
```
It must not contain **any space!** Use a comma to separate values.
The array format supports ranges; the previous example could be rewritten as follow:
```
[1-6,50-52]
```

## Loader (Pawn)
The Pawn version of the Map Loader consist of a single file, MapLoader.inc, which depends on strlib and sscanf2.
In the file you can tweak the limits of each category of item, which affects the total memory used, and the error messages.

There are 4 functions available:
### MapLoader.Load(const fileNameWithoutExtension[])
Loads a .SML file into memory, without creating or removing anything in the game. The fileNameWithoutExtension parameter must not contain the extension.
After this function you could then call Apply() to apply the loaded items, or you could access the loaded data directly to add custom behavior. 
The function returns the total number of errors encountered.

### MapLoader.Apply()
Applies all the loaded items. Has no effect if the cache is empty (MapLoader.Load wasn't called).

### MapLoader.RemoveForPlayer(playerid)
Call this function under OnPlayerSpawn to apply building removals (I don't like hooks).

### MapLoader.Clear()
Completely clears the cache. You normally should never need to use this function, because it gets automatically called by MapLoader.Load(), 
unless you comment the `#define MAPLDR_AUTO_CLEAR` line; if you did, you have the option of manually choosing when to clear the cache.

## Loader (C#)
The C# version of the Map Loader consist of a .NET Core library project, which depends on SampSharp-GameMode, SampSharp-Core and SampSharp-Streamer. 

There is one constructor and 4 public methods available:
### MapLoader(bool autoClear)
Creates an instance of the MapLoader class. The autoClear parameter specifies whether after every call to Load(), the cache should be cleared.
We recommend to pass `true` in this parameter.

### int Load(string fileName, out List<Exception> errors)
Loads a file into memory, without creating or removing anything in the game. The fileName must contain the file extension.
The functions outputs a list of exceptions, containing all the errors that may have occurred, and returns the total number of lines processed.

### void Apply()
Applies all the loaded items. Has no effect if the cache is empty (Load wasn't called).

### void ApplyRemovals(BasePlayer p)
Equivalent of MapLoader.RemoveForPlayer(playerid) of the Pawn version, it applies all building removals, and should be called in the `Spawn` event of
players, or under the `OnSpawned` method in your Player class.

### void Clear()
Completely clears the cache. You should never need to use this method, however if you constructed the MapLoader object with the autoClear parameter set
to false, then you should clear it manually.

## Converter
The Map Converter is a utility that given a file or a list of files, converts them from Pawn to SML and vice-versa.
The converter is lossy, in fact it does not support attached objects, materials and material texts. It will only convert
objects, vehicles and building removals.

To use the converter, simply drag and drop a file or multiple files on the Sasinosoft.MapConverter executable file. It will
automatically convert files with the .pwn extension to .sml, and files with the .sml extension to .pwn.
