# tlotexteditor

A simple text editor.

## Build Requirements

* CMake
* C++14 development environment for which CMake can generate build files
* Qt 5

## Clone, Build, and Run

```
$ git clone <url/to/tlotexteditor.git> # clone into tlotexteditor directory
$ mkdir tlotexteditorbuild
$ cd tlotexteditorbuild
$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ../tlotexteditor
$ make
$ ./tlotexteditor
```
