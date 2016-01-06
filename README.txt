Create a new repository on the command line

touch README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/juwugit/XtoZh.git
git push -u origin master

Push an existing repository from the command line

git remote add origin https://github.com/juwugit/XtoZh.git
git push -u origin master


--

Github seems only supports ssh way to read&write the repo, although https way also displayed 'Read&Write'.

So you need to change your repo config on your PC to ssh way:

   1. edit .git/config file under your repo directory
   2. find url=entry under section [remote "origin"]
   3. change it from url=https://MichaelDrogalis@github.com/derekerdmann/lunch_call.git to url=ssh://git@github.com/derekerdmann/lunch_call.git. that is, change all the texts before @ symbol to ssh://git
   4. Save config file and quit. now you could use git push origin master to sync your repo on GitHub
