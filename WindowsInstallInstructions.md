Please ensure that you are running Windows 10 version 2004 or higher (or windows 11)

Right-Click on the windows icon and select "Run Powershell as Administrator"

In this Powershell window, run the following line

```
wsl --install -d Ubuntu-18.04
wsl --update
```

Once you have this installed, Open the start menu and run "Ubuntu 18.04". It will prompt you to make a new UNIX username and password. Make these something that you will remember.

Once this has finished, go back to your Ubuntu 18.04 window and run the following commands to install and run a test for the GUI support

```
sudo apt update
sudo apt install x11-apps
xeyes
```


After running the commands you should expect to see a window open with a pair of eyes in it. The eyes should follow the mouse

Congratulations! You have finished the first part of the Setup

This next part of the instructions will cover installing the simulation environment. All commands must be run in the Ubuntu 18.04 terminal

```
curl https://gitlab.com/qset-mod-3/unified-launch/-/raw/master/installer.sh | sh -
```

If you get and error saying that curl isn't installed, or it can't find curl you can run `sudo apt install -y curl`
