#!/bin/bash

cp -v bashrc /root/.bashrc
cp -v tmux.conf /root/.tmux.conf
cp -v vimrc /root/.vimrc
cp -v zshrc /root/.zshrc

echo " "
echo "*********************************************************"
echo "*********************************************************"
echo "**                                                     **"
echo "**              running apt-get commands               **"
echo "**                                                     **"
echo "*********************************************************"
echo "*********************************************************"
echo " "

# apt-get update && apt-get upgrade
apt-get -y remove vim
apt-get -y install gcc make
apt-get -y install vim-gtk tmux zsh
apt-get -y install colordiff fortune

echo " "
echo "*********************************************************"
echo "*********************************************************"
echo "**                                                     **"
echo "**               switching shell to zsh                **"
echo "**                                                     **"
echo "*********************************************************"
echo "*********************************************************"
echo " "

chsh -s $(which zsh) root
chsh -s $(which zsh) ubuntu

echo " "
echo "*********************************************************"
echo "*********************************************************"
echo "**                                                     **"
echo "**                creating directories                 **"
echo "**                                                     **"
echo "*********************************************************"
echo "*********************************************************"
echo " "

mkdir  ~/.config
mkdir -p ~/.vim/{backup,bundle,swap,undo}

echo " "
echo "*********************************************************"
echo "*********************************************************"
echo "**                                                     **"
echo "**              cloning git repositories               **"
echo "**                                                     **"
echo "*********************************************************"
echo "*********************************************************"
echo " "

echo "Vundle..."
git clone git://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim
echo "oh-my-zsh..."
git clone git://github.com/robbyrussell/oh-my-zsh.git ~/.config/oh-my-zsh
mv -i ~/cs3210/re5et_dlee440.zsh-theme ~/.config/oh-my-zsh/themes/
echo "base16-shell..."
git clone git://github.com/chriskempson/base16-shell.git ~/.config/base16-shell
echo "zsh-syntax-highlighting..."
git clone git://github.com/zsh-users/zsh-syntax-highlighting ~/.config/oh-my-zsh/custom/plugins/zsh-syntax-highlighting

echo " "
echo "*********************************************************"
echo "*********************************************************"
echo "**                                                     **"
echo "**                      Finished!                      **"
echo "**           Log out and ssh back in as root           **"
echo "**                                                     **"
echo "*********************************************************"
echo "*********************************************************"
echo " "

