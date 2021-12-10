# CITS2002 Project 2

Final grade: 92%

Due date: **11:59pm Friday 22nd October (end of week 12)**

Grade Weighting: **25%**

Authors: Dempsey Thompson, Zach Manson

`duplicates` is a command line utility to locate and report duplicate files in (and below) a named directory based on SHA2 hashes.

## Usage

Compile using command `make` in root directory.

Run `duplicates` using
```
./duplicates directory_path [-a] [-A] [-f filename] [-h SHA2_hash] [-l] [-q]
```

`-a` includes hidden files

`-A` returns 0 as per project requirements

`-f filename` to find duplicates of a single file

`-h SHA2_hash` to match files of a given hash

`-l` to list all duplicate files found

`-q` to execute quietly


## Useful Information:

 + Week 8 Lecture 16 (this content I believe is a big part of project)
 
Project info:
 + [project explanation](https://teaching.csse.uwa.edu.au/units/CITS2002/projects/project2.php)
 + [project clarifications](https://teaching.csse.uwa.edu.au/units/CITS2002/projects/project2-clarifications.php)
 + [sample solution output](https://secure.csse.uwa.edu.au/run/duplicates)
 + [submission location](https://secure.csse.uwa.edu.au/run/cssubmit)  (only 1 member needs to submit)

# Todo
 + [x] plan out program structure
 + [x] figure out how makefiles work
     + [x] setup make on dempsey's pc computers
 + [x] scan directory
 + [x] some kind of hashmap?
 + [x] do flags