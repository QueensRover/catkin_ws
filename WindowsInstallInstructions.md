Please ensure that you are running Windows 10 version 2004 or higher (or windows 11)

Right-Click on the windows icon and select "Run Powershell as Administrator"

In this Powershell window, run the following line

`wsl --install -d Ubuntu-18.04`

If you already have wsl2 installed follow this link to get the correct version of Ubuntu
https://www.microsoft.com/store/apps/9N9TNGVNDL3Q

Once you have this installed, Open the start menu and run "Ubuntu 18.04". It will prompt you to make a new UNIX username and password. Make these something that you will remember.

run the following 3 commands to set up for GUI access
`echo 'export LIBGL_ALWAYS_INDIRECT=0' >> ~/.bashrc`
`echo "export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0" >> ~/.bashrc`
`source ~/.bashrc`


Install VcXsrv. This will allow you to see the simulated robot.
It can be downloaded from https://sourceforge.net/projects/vcxsrv/

Download and run the installer

Once the installer is finished, run XLaunch from the start menu. 
    -- When running this use the default settings except uncheck "Native opengl" and check "Disable access control"
    -- I would advise saving the configuration

Once this has finished, go back to your Ubuntu 18.04 window and run the following commands to install and run a test for the GUI support you have just added
`sudo apt update`
`sudo apt install x11-apps`
`xeyes`

After running the commands you should expect to see a window open with a pair of eyes in it. The eyes should follow the mouse

Congratulations! You have finished the first part of the Setup

This next part of the instructions will cover installing the simulation environment. All commands must be run in the Ubunut 18.04 terminal

`curl https://gitlab.com/qset-mod-3/unified-launch/-/raw/master/installer.sh | sh -`
