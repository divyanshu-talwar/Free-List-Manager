free-list-manager: free-list-manager.c
	gcc -g -o free-list-manager free-list-manager.c -lreadline
	gnome-terminal -e ./free-list-manager

clean:
	rm -f free-list-manager