THE PROGRAM WAS CREATED ON LINUX (UBUNTU) IN Qt5

INSTALLATION (UBUNTU):

1. Download "Note.zip".
2. Unpack "Note.zip".
3. Move the "Note" folder to your home folder.
4. Open activities, find the "Startup Applications" program and run it.
5. Press "add".
6. In the "Name:" field, enter "noteScheduler".
7. In the "Command:" field enter "/home/"username"/Note/noteScheduler" replacing "username" with the name of the current user.
8. Press "add".
9. Create a link to the "DB" file by entering "ln -s /home/"username"/Note/DB /home/"username"" in command prompt (if such a file already exists, delete it and enter the command again).
10. Log out and log back in.

IF YOU WANT TO RUN THE PROGRAM FROM COMMAND PROMPT:
11. Open command prompt, go to the "Note" folder and type "./note123".

IF YOU WANT TO RUN THE PROGRAM FROM ACTIVITIES:
11. Open the "note.desktop" file in the "Note" folder.
12. Change "username" for "Exec" and "username" for "Icon" to the name of the current user and save the file.
13. Move the "note.desktop" file to "/home/"username"/.local/share/applications/".
14. Log out and log back in.
15. Open activities, find the "Note" program and run it.

USE OF SOURCE CODE:
In "note/data.cpp" on line 3 and in "noteScheduler/main.cpp" on lines 44 and 76, there are paths to change.
