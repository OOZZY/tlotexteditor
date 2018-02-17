# tlotexteditor

A simple text editor.

## Build Requirements

* CMake
* C++14 development environment for which CMake can generate build files
* Qt 5

## Clone, Build, and Run

Clone into tlotexteditor directory.

```
$ git clone --branch develop <url/to/tlotexteditor.git>
```

Build.

```
$ mkdir tlotexteditorbuild
$ cd tlotexteditorbuild
$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ../tlotexteditor
$ make
```

Run.

```
$ ./src/tlotexteditor
```
