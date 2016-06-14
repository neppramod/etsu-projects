#!/bin/bash
##################################################################
#	Script for adding multiple users to the system using a 
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

# This generates the default password. useradd has to pass the 
# encrypted form of the password with the -p switch. The following
# two lines generate the encrypted password and store it in the 
# variable $pass
password="pass"
pass=$(perl -e 'print crypt($ARGV[0], "password")' $password)

count=0		# counter to display the number of users added
		# at the end of the job

# check for the right number of arguments. If the filename parameter
# is missing, user will be advised of the usage and execution will 
# terminate. Note that this script does not check to see that the 
# file, if present in the command line, is formatted correctly.
if (( $# != 1 ));
then
	echo "Usage: sudo museradd [filename]"
	echo "You need to specify a valid filename!"
	exit 1
fi

echo "$(whoami)"

if [ "$(whoami)" != "root" ]; 	# checking that the user has elevated privileges
then	
	echo "Your UID is $(id -u)"
	echo "Only root can add a user to the system"
	exit 2				
fi

while read f1 f2 f3  		# read the first line into $f1, $f2, and $f3
do

        echo "New user name is: $f1 ($f2 $f3)"

	egrep "^$f1" /etc/passwd >/dev/null	# check if username already exists
	if [ $? -eq 0 ]; then			# if so,
		echo "User $f1 exists! Cannot add..."
	else					# if not:
		# add the user. The  --password switch sets the password to the 
		# default, -c switch stores the users full name, -s switch sets
		# the users default shell, and -m generates the users home directory.
		useradd $f1 --password $pass -c "$f2 $f3" -s /bin/bash -m
		mkdir /var/mail/"$f1"
		chown $f1:$f1 /var/mail/"$f1"
		# set password age to 0, forcing the user to change it when they
		# log in the first time.
		chage -d 0 $f1
		if [ $? -eq 0 ]; then 
			echo "User has been added to system!"
		else	
			echo "Error! User could not be added"
		fi
		echo
		((count++)) 	## increment the counter
	fi

done < "$1"

	echo
	echo "Job completed. $count users added to the system"
	echo
	echo "Press Enter to continue..."
	read in			# pause output
	clear			# clear the terminal when user presses Enter
