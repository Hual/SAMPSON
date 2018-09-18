SAMPSON
=======

SAMPSON - A JSON plugin for SA-MP

### Why?
I decided to build this plugin as a fellow member of the SA-MP community was having issues with DJSON. DJSON is also outdated and does not conform to various JSON standards. It caches to disk, has a large memory footprint, and uses SQL for... JSON storage. It seemed wrong to me, so I decided to build my own plugin.

### Features:  
The plugin currently features a JSON parser for files located in your 'scriptfiles' directory. It's compliant to the JSON standards and can parse strings, numbers, booleans and arrays.

### Documentation:
I'll be doing tutorials on the usage of this plugin, and a Wiki for all the functions. But for now, I'll just dump the functions with basic information about them here:

You can define a node delimiter by defining JSON_DEFAULT_DELIMITER to a char; Default delimiter is
```
#define JSON_DEFAULT_DELIMITER '/'
```
---

##### `json_parse_file`
```
native JSONNode:json_parse_file(const file_path[])
```
>Function: Reads a file, parses it, and stores it in memory for further parsing.  
>Returns: A handle to the root node.

##### `json_parse_string`
```
native JSONNode:json_parse_string(const string[])
```
>Function: Parses a string and stores it in memory for further parsing.  
>Returns: A handle to the root node.

##### `json_close`
```
native json_close(JSONNode:node)
```
>Function: Closes a JSON file with root node 'node' and frees all memory associated with it.  
>Returns: 1 on success, 0 on failure.

##### `json_get_type`
```
native json_get_type(JSONNode:node, const path[] = '\0', const path_delim = JSON_DEFAULT_DELIMITER)
```
>Function: Gets the type of a node's value.  
>Returns: An integer representing the node's value type. See below for type definitions.

```
JSON_NULL
JSON_STRING
JSON_NUMBER
JSON_BOOL
JSON_ARRAY
JSON_NODE
```
##### `json_get_node`
```
native JSONNode:json_get_node(JSONNode:node, const path[], const path_delim = JSON_DEFAULT_DELIMITER)
```
>Function: Gets the node at some path using 'node' as a root node.  
>Returns: The node on success, 0 if the node doesn't exist.

##### `json_get_bool`
```
native bool:json_get_bool(JSONNode:node, const path[] = '\0', const path_delim = JSON_DEFAULT_DELIMITER)
```
>Function: Gets the value of some path using 'node' as a root node as a boolean.  
>Returns: The value of the specified path's key as a boolean.

##### `json_get_int`
```
native json_get_int(JSONNode:node, const path[] = '\0', const path_delim = JSON_DEFAULT_DELIMITER)
```
>Function: Gets the value of some path using 'node' as a root node as an integer.  
>Returns: The value of the specified path's key as an integer.

##### `json_get_float`
```
native Float:json_get_float(JSONNode:node, const path[] = '\0', const path_delim = JSON_DEFAULT_DELIMITER)
```
>Function: Gets the value of some path using 'node' as a root node as a float.  
>Returns: The value of the specified path's key as a float.

##### `json_get_string`
```
native json_get_string(JSONNode:node, dst[], const len = sizeof(dst), const path[] = '\0', const bool:packed = false, const path_delim = JSON_DEFAULT_DELIMITER)
```
>Function: Gets the value of some path using 'node' as a root node as a string and writes it to 'dst'.  
>Returns: 1.

##### `json_get_name`
```
native json_get_name(JSONNode:node, dst[], const len = sizeof(dst), const bool:packed = false)
```

>Function: Gets the name (key) of some path using 'node' as a root node and writes it to 'dst'.  
>Returns: 1 if the node has a name (key) associated with it, 0 if it doesn't.

##### `json_get_array`
```
native JSONArray:json_get_array(JSONNode:node, const path[] = '\0', const path_delim = JSON_DEFAULT_DELIMITER)
```
>Function: Gets the value of some path using 'node' as a root node as an array.  
>Returns: A JSON array type which is used for array functions.

##### `json_array_count`
```
native json_array_count(JSONArray:array)
```
>Function: Gets the amount of elements 'array' contains.  
>Returns: An integer representing the amount of elements 'array' contains.

##### `json_array_at`
```
native JSONNode:json_array_at(JSONArray:array, const index)
```
>Function: Gets the element at 'index' in 'array' as a node.  
>Returns: The element as a JSON node.

### Installation
Download the [release archive](https://github.com/Hual/SAMPSON/releases) and place its contents into your server folder. Open your configuration file and add 'SAMPSON' ('SAMPSON.so' on Linux) to your 'plugins' line.

### Building from source
1. Download the source code from the link provided above.
2. On Windows, open the 'SAMPSON.sln' file in Visual Studio, select 'Release' build target and then build it.
3. On Linux, run 'make' in the 'src' folder. The built plugin should be found in the 'build' folder.


### Credits
- The SA-MP team - SA-MP, SA-MP plugin SDK
- Djole1337 - Testing support, Linux build support

