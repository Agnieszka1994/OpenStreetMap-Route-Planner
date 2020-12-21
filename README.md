# OpenStreetMap Route Planner

This repo contains the final project of the 1st Udacity Nanodegree C++ course.
The project is an extension of the IO2D map display code that uses A* algorithm to find a path between two points on the map.

## Requirements

- compiler support for C++17 (gcc/g++ >= 5.4).
- cmake >= 3.11
- make >= 4.1 (Linux, Mac), 3.81 (Windows)
- **additional libraries** `pugixml` and `io2d` installed. 

## Get started
```shell
git clone https://github.com/Agnieszka1994/OpenStreetMap-Route-Planner
cd OpenStreetMap-Route-Planner/
mkdir build && cd build/
cmake ..
make
./OSM_A_star_search
```
**Testing**
```shell
./test
```

## How to use Route Planner

Once the program is compiled and run, it asks the user for 4 coordinates ranging from 0 to 99: `start x`, `start y`, `end x` and `end y`. Then it calculates the distance between these two points and renders the road from the `start` point to the `end` on the map. The map in `.osm` format must be named `map.osm` and placed in the project directory. A sample map is attached to the repo, but you can download your own from the page below.

[Download maps here.](https://www.openstreetmap.org/) 

## Sample Usage 1 - Warsaw - Old Town

```
Usage: [executable] [-f filename.osm]
Reading OpenStreetMap data from the following file: Warsaw_old_town.osm
Enter start x btw. 0 - 99: 20
Enter start y btw. 0 - 99: 20
Enter end x btw. 0 - 99: 60
Enter end y btw. 0 - 99: 70

```
Program output:
```
Distance: 1190.83 meters.
```
[![img](https://github.com/Agnieszka1994/OpenStreetMap-Route-Planner/blob/main/images/old_town.png)](https://github.com/Agnieszka1994/OpenStreetMap-Route-Planner/blob/main/images/)

## Sample Usage 2 - Warsaw - Praga District
```
Usage: [executable] [-f filename.osm]
Reading OpenStreetMap data from the following file: Warsaw_Praga.osm
Enter start x btw. 0 - 99: 10
Enter start y btw. 0 - 99: 10
Enter end x btw. 0 - 99: 80
Enter end y btw. 0 - 99: 90
```
Program output:
```
Distance: 2002.04 meters.
```
[![img](https://github.com/Agnieszka1994/OpenStreetMap-Route-Planner/blob/main/images/Warsaw_Praga.png)](https://github.com/Agnieszka1994/OpenStreetMap-Route-Planner/blob/main/images/)
