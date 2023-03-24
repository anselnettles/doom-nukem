<h2>Drowning | "𝘋𝘰𝘰𝘮-𝘕𝘶𝘬𝘦𝘮" | 𝘢𝘯 𝘶𝘯𝘥𝘦𝘳𝘸𝘢𝘵𝘦𝘳 𝘵𝘩𝘳𝘦𝘦-𝘥𝘪𝘮𝘦𝘯𝘴𝘪𝘰𝘯𝘢𝘭 𝘴𝘶𝘳𝘷𝘪𝘷𝘢𝘭-𝘨𝘢𝘮𝘦</h2>
<i>Summary: This C project is about creating a 3D polygonal game with ray-casting technique, that utilizes no GPU. Just like the breakthrough shooter games in the 90s. </i><br><br>
This was the final "core-studies project" of the game-graphics branch in HIVE Helsinki, A "42-style" coding school. The goal of the project is to create a first-person game in a "3D graphic representation". This would have to be achieved via a raycasting method. No computer hardware acceleration and no 3D library are allowed.<br><br>

<div align ="center">Everything in this project was coded from scratch by a group of three – in C language.<br><br>

<div align="left"><b>This game features:</b><br>

<p><input size="120">
<h3>• Real-time three-dimensional movement and view angles via keyboard and mouse.<br> 
• A feature-rich game stage, with a variety of environmental heights, nooks and un-even terrain.<br>
• Fully original environmental textures, parsed internally from a HEX sprite graphics map.<br> 
• Collectible items, environmental events and details that are constantly shifting.<br> 
• An atmospheric setting and background music to support the moody story.<br> 
• A level-editor that allows the user to edit and adjust the game stage to their likings.</h3> 
</input></p></br>

#
![drowning_optimized_demo](https://user-images.githubusercontent.com/70949716/225095125-ea451c08-9c18-4272-ac6b-9a13600a5af2.gif)

&emsp;&emsp;<sup><b>As of January 24th 2023, the work became a  collaboration project with @Dofidog (Topi Paaso) and @UItsi (Timo Turto).</sup></b><br>
&emsp;&emsp;<sup><b>Project Drowning will be fully finished by April 2023.</sup></b>
#

<h3>Controls:</h3>

<b>• `W`, `A`,`S`,`D`, moves and strafes the player underwater. `Left Shift` allows you to run.</b><br>
 &emsp;&emsp;<sup>The player slowly builds up speed and momentum when in motion, making stopping also more difficult.</sup><br>
<b>• `Space` lets you jump.</b><br>
 &emsp;&emsp;<sup>Being underwater, the jump has quite a bit of floaty momentum to it. See how far you can reach!</sup><br>
<b>• `C` makes the character crouch.</b><br>
 &emsp;&emsp;<sup>You can slightly adjust viewing angle with a crouch.</sup><br>
<b>• `E` picks up items.</b><br>
 &emsp;&emsp;<sup>The lake bottom is scattered with collectible items, such as oxygen flasks and harpoons for the player to find.</sup><br>
 <b>• `F` turns on the lantern light.</b><br>
 &emsp;&emsp;<sup>It's imperative to use the light to see where you're stepping underneath the dark surface.</sup><br>
<b>• `F3` toggles Dev Mode.</b><br>
 &emsp;&emsp;<sup>Developer mode off color filters and overlay textures. Allows the user to swim upwards by tapping the jump key.</sup><br><br>

<h3>Making-of footage:</h3>

#
https://user-images.githubusercontent.com/70949716/218528549-8c36df09-ce95-4925-8694-3ef48165a632.mov 

 &emsp;&emsp;<sup>In very early stages of development, we were still examining draw distancing, texture scaling and the conversion of the map file.</sup>
