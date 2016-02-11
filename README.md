# CFlip (Craft Flip) Guild Wars 2 Financial Application

CFlip is an optimization tool for the Guild Wars 2 game.
Given an item, it will compute the most profitable steps of buying and
crafting materials to sell.

**Note**: This first time running the application will take a very long time
(5-10 minutes) while building the files it needs.

## Example Screenshots
![img1](http://i.imgur.com/w8J9BqF.png)

![img2](http://i.imgur.com/3WqFIK0.png)

## Build Instructions

1. Clone the repo
	`git clone git@github.com:terminull/CFlip.git`
2. Make sure your build environment is using at least Qt 5.5
3. Follow the normal build instructions for your operating system for building a
  Qt app. CFlip has no dependencies outside of Qt. The project file is `src/CFlip.pro`

**Note**: If you are on OSX, you need to add this `src/CFlip.pro`:

```
CONFIG -= app_bundle
```
