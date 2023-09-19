**This is a school project that I really liked, so I am posting it here**

This was pulled from a private archive on UTA Servers and developed on my school Github account (ctb9024), so unfortunately the commit history was not preserved

This was the semester project for my Fundamentals of Software Engineering class, and it taught me a lot about working in teams (and exFat file systems, but I don't think that was the point of the project)
    The project was developed with an Agile approach over 3 sprints, with requirements constantly changing
    A lot of the code here was included in a template, but everything in "src" and "tests" was written by the 4 members of the project (to my knowledge)
    
I was responsible for multiple parts of the project, such as Initial System Design/Coordination, most of the Automated System Tests, and most of the File Handling

The project was developed and tested in the cloud on Github Codespaces




extfat utils is a utility to manipulate extfat images.

# Command Options:
./extfat -i "input file"

./extfat -o "output file"

./extfat -h (provides a descriptive help menu of the current commands that are expected to be implemented)

./extfat -v -i "input file" (verifies the boot records)

./extfat -c -i "input file" -o "output file" (copies input into output)

./extfat -d -i "input file" (prints directories of input file)


# Example Invocations:
< Provide examples of use here >


# Internals

## Build Process
```bash
% make clean
% make

To run the tests
% make tests

```

## Examples
There is a directory of examples.  They are compiled by default using the makefile
Before you can run the example programs, you need to have an file image.

```bash
% bash /examples/create_image.bash
% ./examples/fread
% ./examples/mmap
```




















## Misc notes, eventually delete.
```
dd if=/dev/zero of=zzz count=1 bs=1G
yum install -y exfat-utils fuse fuse-exfat
losetup /dev/loop0 diskimage 
mount /dev/loop0 /mnt
umount /mnt
```
## References


https://pawitp.medium.com/notes-on-exfat-and-reliability-d2f194d394c2


https://learn.microsoft.com/en-gb/windows/win32/fileio/exfat-specification


https://uta.service-now.com/selfservice?id=ss_kb_article&sys_id=KB0011414


https://nemequ.github.io/munit/#download


https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html


https://www.freecodecamp.org/news/how-to-use-git-and-github-in-a-team-like-a-pro/


https://en.wikipedia.org/wiki/ExFAT


https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax
