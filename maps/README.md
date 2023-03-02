## Map ASCII legends:<br>

`#`       : Full wall height<br>
`1` - `9` : Floor height<br>
`/`       : 45° wall northwest (Referred floor height on northwest side, neighboring floor height (south) on southeast)<br>
`\`       : 45° wall northeast (Referred floor height on northeast side, neighboring floor height (south) on southwest)<br>
`<`       : 45° wall southwest (Referred floor height on southwest side, neighboring floor height (north) on northeast)<br>
`>`       : 45° wall southeast (Referred floor height on southeast side, neighboring floor height (north) on northwest)<br>
`*`       : Full height pillar<br>
`a` - `c` : Texture reference<br>
`X`       : Player start position<br>
`Z`       : Player goal location<br>
`I`       : Collectible item: Bottle. Oxygen replenishment.<br>
`R`       : A map square with a ceiling texture over it. A roof of cubes should be applied over this square up to full height (`#`)<br><br>

`map[x][y][z]`<br><br>
`x`/`y`   : Coordinates.<br>
`z`       : Parameter indicating what the coordinate contains.<br>
            <i>Example: </i>`[][][0]` = wall height, `[][][1]` = wall texture type... `[][][n]`<br><br>
 
 <i>Example</i>
```
#a/PR 1b>G. 2c\MR #a/PR
..... #.>N. .b>KR .....
#c/I. ..... #c/.. .....
..... ..... ..... .....
!texture_0={0xff8fbecf, 0xff8fbecf, 
0xff8fbecf, 0xff8fbecf, 
0xff8fbecf, 0xff8fbecf},
texture_1={...}!
~sprite_arm_right0={...},sprite_arm_right1{...},sprite_arm_right2{...}~
@sprite_arm_left={...}$@
?sprite_weed={...}?
+sprite_projectile={...}+
|sprite_monster0={...}|
$sprite_collectible0={...}$
&sprite_goal={...}&
"sprite_breakable={...}"
%sprite_glass={...}%'\n'
```

`.`       : Ignore option during `render()`.<br><br>

0:  Block height<br>
    chars->param0_choice0 = '#';<br>
    chars->param0_choice1 = '1';<br>
    chars->param0_choice2 = '2';<br>
    chars->param0_choice3 = '3';<br>
    chars->param0_choice4 = '4';<br>
    chars->param0_choice5 = '5';<br>
    chars->param0_choice6 = '6';<br>
    chars->param0_choice7 = '7';<br>
    chars->param0_choice8 = '8';<br>
    chars->param0_choice9 = '.';<br><br>

1:  Texture<br>
    chars->param1_choice0 = 'a';<br>
    chars->param1_choice1 = 'b';<br>
    chars->param1_choice2 = 'c';<br>
    chars->param1_choice3 = '.';<br><br>

2:  "45 degree"<br>
    chars->param2_choice0 = '/';<br>
    chars->param2_choice1 = '\\';<br>
    chars->param2_choice2 = '>';<br>
    chars->param2_choice3 = '<';<br>
    chars->param2_choice4 = '.';<br><br>

3:  Entity<br>
    chars->param3_choice0 = 'P';    //player_start<br>
    chars->param3_choice1 = 'G';    //goal<br>
    chars->param3_choice2 = 'M';    //monster1<br>
    chars->param3_choice3 = 'N';    //monster2<br>
    chars->param3_choice4 = 'I';    //item1<br>
    chars->param3_choice5 = 'J';    //item2<br>
    chars->param3_choice6 = 'K';    //item3<br>
    chars->param3_choice7 = '.';<br><br>

4:  Special<br>
    chars->param4_choice0 = 'R';    //"Secret path". Contains a hard-coded transparency value.<br>
                                    //  Renders a ceiling on top of the i0(0)_wall_height_choice (WHC).<br>
                                    //  Distance between WHC - Roof = hard-coded, e.g. 1 cube<br>
    chars->param4_choice1 = '*';    //"Pillar to infinity"<br>
    chars->param4_choice2 = '.';<br><br><br>

## Identity marks for begin and end of texture information:
<br>

Texture `A`, 0:		Floor texture.  Frames: 0.	  		Size: 64 x 64 <br>
Texture `B`, 1:		Wall texture.	  Frames: 0.	  		Size: 64 x 64 <br>
Texture `C`, 2:		Pillar texture.	Frames: 0.	  		Size: 64 x 64 <br>
Texture `D`, 3:		Crate texture.	Frames: 0.	  		Size: 64 x 64 <br>
Texture `E`, 4:		Sky texture.	  Frames: 0.	  		Size: 720 x 240 <br>
Texture `F`, 5:		Right arm.	   	Frames: 0 to 4.	  Size: 250 x 238 <br>
Texture `G`, 6:		Letters.	    	Frames: 0.			  Size: 728 x 20 <br> 
Texture `H`, 7:		Harpoon.	    	Frames: 0 to 6.		Size: 64 x 64 <br>
Texture `I`, 8:		Bottle.		  	  Frames: 0 to 3.		Size: 38 x 64 <br>
Texture `J`, 9:		Timer.		    	Frames: 0 to 9.		Size: 60 x 90 <br>
Texture `K`, 10:	Bubble.		    	Frames: 0.		  	Size: 12 x 12 <br>
Texture `L`, 11:	Ammo.			      Frames:	0 to 1.		Size: 32 x 45 <br>
Texture 'M', 12:  Monster.        <br>
Texture 'N', 13:  Algae.        Frames: 0 to 4.   Size: 64 x 64 <br>

## In-recorded textures graphics:
<br>

`drown->gfx.txt.texture_a[64][64]` : Floor.<br> 

![image](https://user-images.githubusercontent.com/70949716/216399368-b52723d5-13c3-40b9-92d7-0153e7ee3758.png) <br>

`drown->gfx.txt.texture_b[64][64]` : Wall.<br>

![image](https://user-images.githubusercontent.com/70949716/216617733-ba63c1f7-67b5-49d9-944a-1092b340e125.png) <br>

`drown->gfx.txt.texture_c[64][64]` : Pillar.<br>

![image](https://user-images.githubusercontent.com/70949716/216831640-89a83d30-060e-4251-9ac7-59f3d895c929.png) <br>

`drown->gfx.txt.texture_d[64][64]` : Crate.<br> 

![image](https://user-images.githubusercontent.com/70949716/216399608-7c2a9388-4216-4df1-b475-a01df5fe807c.png) <br>

`drown->gfx.txt.skybox[64][128]`  : Water surface.<br> 

![image](https://user-images.githubusercontent.com/70949716/216763126-8dc46de6-ee83-449e-aff6-b13f54279044.png) <br>

## To be included: (To be re-written)
<br>

`drown->gfx.sprite.weed[3][48][20];`  : Seaweed. Animated. Used aplenty. <br>

`drown->gfx.sprite.moss[60][60];` : Sea moss/foliage. Not necessarily animated. Used aplenty. <br>

`drown->gfx.sprite.foliage[128][128];`  : Some see-through foliage. Necessary for "see-through wall" requirement.

`drown->gfx.sprite.goal[6][128][64];` : The dangling rope in the surface. Probably needs to be quite visible and animated.

`drown->gfx.sprite.left_arm[?][?][?];`  : Overlay. Player's left arm. The weapon. More frames than left arm due to weapon animation. <br>

`drown->gfx.sprite.monster[8][3][128][128];`  : Possibly the most demanding graphic piece. The monster, viewed from eight direction with with three frames each. Could be a four-dimensional array? <br>

`drown->gfx.sprite.ammo[3][12][12];`  : Overlay HUD. Remaining ammo in weapon. Probably animated. <br>

`drown->gfx.storyboard.title_screen[642][480];` : Title splash screen. One or a few frames. <br>

`drown->gfx.storyboard.beginning[3][642][480];` : Starting cutscene. Three or four frames. <br>

`drown->gfx.storyboard.bad_end[3][642][480];` : Ending cutscene. Three or four frames. Monster wins. <br>

`drown->gfx.storyboard.good_end[3][642][480];`  : Ending cutscene. Three or four frames. Player wins. <br>
