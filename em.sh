jungle@1f2bf40864ca:/workspaces/rbtree_lab_docker/rbtree_lab/test$ make test
gcc -I ../src -Wall -g -DSENTINEL -c test-rbtree.c -o ../out/obj/test-rbtree.o
gcc -I ../src -Wall -g -DSENTINEL -c ../src/rbtree.c -o ../out/obj/rbtree.o
gcc -I ../src -Wall -g -DSENTINEL -o ../out/bin/test-rbtree ../out/obj/test-rbtree.o ../out/obj/rbtree.o
/usr/bin/ld: ../out/obj/test-rbtree.o: in function `test_find_single':
/workspaces/rbtree_lab_docker/rbtree_lab/test/test-rbtree.c:48:(.text+0x25c): undefined reference to `rbtree_find'
/usr/bin/ld: /workspaces/rbtree_lab_docker/rbtree_lab/test/test-rbtree.c:53:(.text+0x2fc): undefined reference to `rbtree_find'
/usr/bin/ld: ../out/obj/test-rbtree.o: in function `test_find_erase':
/workspaces/rbtree_lab_docker/rbtree_lab/test/test-rbtree.c:360:(.text+0x146c): undefined reference to `rbtree_find'
/usr/bin/ld: /workspaces/rbtree_lab_docker/rbtree_lab/test/test-rbtree.c:369:(.text+0x1530): undefined reference to `rbtree_find'
/usr/bin/ld: /workspaces/rbtree_lab_docker/rbtree_lab/test/test-rbtree.c:377:(.text+0x15f4): undefined reference to `rbtree_find'
/usr/bin/ld: ../out/obj/test-rbtree.o:/workspaces/rbtree_lab_docker/rbtree_lab/test/test-rbtree.c:382: more undefined references to `rbtree_find' follow
collect2: error: ld returned 1 exit status
make: *** [Makefile:43: ../out/bin/test-rbtree] Error 1

jungle@1f2bf40864ca:/workspaces/rbtree_lab_docker/rbtree_lab/test$ make test
gcc -I ../src -Wall -g -DSENTINEL -c test-rbtree.c -o ../out/obj/test-rbtree.o
gcc -I ../src -Wall -g -DSENTINEL -c ../src/rbtree.c -o ../out/obj/rbtree.o
gcc -I ../src -Wall -g -DSENTINEL -o ../out/bin/test-rbtree ../out/obj/test-rbtree.o ../out/obj/rbtree.o

jungle@1f2bf40864ca:/workspaces/rbtree_lab_docker/rbtree_lab$ ./out/bin/test-rbtree
test-rbtree: test-rbtree.c:132: test_minmax: Assertion `p->key == arr[1]' failed.
Aborted

jungle@1f2bf40864ca:/workspaces/rbtree_lab_docker/rbtree_lab$ make clean
make -C src OUT_DIR=/workspaces/rbtree_lab_docker/rbtree_lab/out clean
make[1]: Entering directory '/workspaces/rbtree_lab_docker/rbtree_lab/src'
rm -f /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/*.o /workspaces/rbtree_lab_docker/rbtree_lab/out/bin/driver
make[1]: Leaving directory '/workspaces/rbtree_lab_docker/rbtree_lab/src'
make -C test OUT_DIR=/workspaces/rbtree_lab_docker/rbtree_lab/out clean
make[1]: Entering directory '/workspaces/rbtree_lab_docker/rbtree_lab/test'
rm -f /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/visualize-main.o /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/rbtree_visualizer.o /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/rbtree.o /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/test-rbtree.o /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/rbtree.o /workspaces/rbtree_lab_docker/rbtree_lab/out/bin/test-rbtree /workspaces/rbtree_lab_docker/rbtree_lab/out/bin/visualize_rbtree /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/rbtree.o
make[1]: Leaving directory '/workspaces/rbtree_lab_docker/rbtree_lab/test'
rm -rf /workspaces/rbtree_lab_docker/rbtree_lab/out

jungle@1f2bf40864ca:/workspaces/rbtree_lab_docker/rbtree_lab$ make test
make -C test OUT_DIR=/workspaces/rbtree_lab_docker/rbtree_lab/out SRC_DIR=/workspaces/rbtree_lab_docker/rbtree_lab/src run-test check-test
make[1]: Entering directory '/workspaces/rbtree_lab_docker/rbtree_lab/test'
gcc -I ../src -Wall -g -DSENTINEL -c test-rbtree.c -o /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/test-rbtree.o
gcc -I ../src -Wall -g -DSENTINEL -c /workspaces/rbtree_lab_docker/rbtree_lab/src/rbtree.c -o /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/rbtree.o
gcc -I ../src -Wall -g -DSENTINEL -o /workspaces/rbtree_lab_docker/rbtree_lab/out/bin/test-rbtree /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/test-rbtree.o /workspaces/rbtree_lab_docker/rbtree_lab/out/obj/rbtree.o
→ Running test
test-rbtree: test-rbtree.c:132: test_minmax: Assertion `p->key == arr[1]' failed.
Aborted
make[1]: *** [Makefile:33: run-test] Error 134
make[1]: Leaving directory '/workspaces/rbtree_lab_docker/rbtree_lab/test'
make: *** [Makefile:20: test] Error 2

jungle@1f2bf40864ca:/workspaces/rbtree_lab_docker/rbtree_lab/test$ ../out/bin/test-rbtree
test-rbtree: test-rbtree.c:132: test_minmax: Assertion `p->key == arr[1]' failed.
Aborted