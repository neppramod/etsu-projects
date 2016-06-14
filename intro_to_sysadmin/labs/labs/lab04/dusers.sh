#!/bin/bash
##################################################################
#	Script for deleting multiple users from a system using a 
#	text file containing space delimited fields, one per line
#	in the format "username firstname lastname".
#	This script uses the "useradd" command to generate
#	accounts for each user, including creating home 
#	directories and copying skel files to them.
#
#	The default password is set to "pass". The user will be
#	required to change his/her password at first login.
##################################################################
clear   # clear the terminal screen

count=0		# counter to display the number of users deleted
		# at the end of the job

# check for the right number of arguments. If the filename parameter
# is missing, user will be advised of the usage and execution will 
# terminate. Note that this script does not check to see that the 
# file, if present in the command line, is formatted correctly.
if (( $# != 1 ));
then
	echo "Usage: sudo dusers [filename]"
	echo "You need to specify a valid filename!"
	exit 1
fi

echo "$(whoami)"

if [ "$(whoami)" != "root" ]; 	# checking that the user has elevated privileges
then	
	echo "Your UID is $(id -u)"
	echo "Only root can delete a user to the system"
	exit 2				
fi

while read f1 f2 f3  		# read the first line into $f1, $f2, and $f3
do

        echo "User name is: $f1 ($f2 $f3)"

	egrep "^$f1" /etc/passwd >/dev/null	# check if username already exists
	if [ $? -eq 0 ]; then			# if so,
		# first delete user's mail directory if exists
		# delete the user. 
		# Before deleting the user make sure to remove /var/mail/<username> directory
		# And after deleting the user remove the user's home directory
		rm -rf /var/mail/$f1	
		userdel $f1
		rm -rf /home/$f1

		if [ $? -eq 0 ]; then 
			echo "User has been deleted from the system!"
		else	
			echo "Error! User could not be deleted"
		fi
		echo
		((count++)) 	## increment the counter
		

	else					# if not:
				echo "User $f1 does not exist! Cannot deleted..."
	fi

done < "$1"

	echo
	echo "Job completed. $count users deleted from the system"
	echo
	echo "Press Enter to continue..."
	read in			# pause output
	clear			# clear the terminal when user presses Enter
