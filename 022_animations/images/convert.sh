#!/bin/bash

ls -1 pexel*.jpg | while read a; do convert $a -scale 640x640 -gravity Center -extent 1:1 sq_$a; done

