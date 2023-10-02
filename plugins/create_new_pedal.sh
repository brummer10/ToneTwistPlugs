#!/bin/bash

set -e

########################## functions ###################################

function usage() {
  echo "usage: create_new_pedal -n NewPlugName  "
  echo "options:"
  echo "    -h:   show this help"
  echo "    -n    effect name "
  exit 1
}

function createPedal() {
  if [ -d ./"$effect_name" ]; then
    echo "$effect_name does already exist. --> EXIT"
    exit 1
  fi

  echo "Create Pedal source for $effect_name"

  cp -Ru ./NewPedal/ ./"${effect_name}"
  rename 's/NewPedal/'"${effect_name}"'/g' ./"${effect_name}"/*
  sed -i 's/NewPedal/'"${effect_name}"'/g' ./"${effect_name}"/*
  sed -i 's/NEWPEDAL/'"${effect_name^^}"'/g' ./"${effect_name}"/*
  sed -i 's/newpedal/'"${effect_name,,}"'/g' ./"${effect_name}"/*

  echo "Done"
}

############################# main #####################################

effect_name=""

while getopts hn: OPT; do
  sc=0
  case "$OPT" in
  h) usage;;
  n) effect_name=$OPTARG;;
  \?) usage;;
  esac
  if [ $OPTIND != 1 ] # This test fails only if multiple options are stacked
                        # after a single -.
  then    shift $((OPTIND - 1 + sc))
     OPTIND=1
  fi
done

if [ -z "$effect_name" ]
then
  echo  -e "Please give a Name for the new Pedal -n NewPedal"
  usage
else
  createPedal
fi

############################ EOF #######################################

exit
