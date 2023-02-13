## ASCII legends:
<br>

`#`       : Full wall height<br>
`1` - `9` : Floor height<br>
`/`       : 45° wall northwest (Referred floor height on northwest side, neighboring floor height (south) on southeast)<br>
`\`       : 45° wall northeast (Referred floor height on northeast side, neighboring floor height (south) on southwest)<br>
`<`       : 45° wall southwest (Referred floor height on southwest side, neighboring floor height (north) on northeast)<br>
`>`       : 45° wall southeast (Referred floor height on southeast side, neighboring floor height (north) on northwest)<br>
`*`       : Full height pillar<br>
`a` - `c` : Texture reference<br>
`S`       : Player start position<br>
`G`       : Player goal location<br>
`R`       : A map square with a ceiling texture over it. A roof of cubes should be applied over this square up to full height (`#`)<br>

## In-recorded textures graphics:
<br>

`drown->txt.texture_a[64][64]` : Floor.<br> 

![image](https://user-images.githubusercontent.com/70949716/216399368-b52723d5-13c3-40b9-92d7-0153e7ee3758.png) <br>

`drown->txt.texture_b[64][64]` : Wall.<br>

![image](https://user-images.githubusercontent.com/70949716/216617733-ba63c1f7-67b5-49d9-944a-1092b340e125.png) <br>

`drown->txt.texture_c[64][64]` : Pillar.<br>

![image](https://user-images.githubusercontent.com/70949716/216831640-89a83d30-060e-4251-9ac7-59f3d895c929.png) <br>

`drown->txt.texture_d[64][64]` : Crate.<br> 

![image](https://user-images.githubusercontent.com/70949716/216399608-7c2a9388-4216-4df1-b475-a01df5fe807c.png) <br>

`drown->txt.skybox[64][128]`  : Water surface.<br> 

![image](https://user-images.githubusercontent.com/70949716/216763126-8dc46de6-ee83-449e-aff6-b13f54279044.png) <br>

`drown->sprite.right_arm[3][238][250];` : Overlay. Player's right arm.<br>

`drown->sprite.letters[20][728];` : Font set sprite. Includes the necessary characters for 'gfx_write()'. <br>

## To be included: 
<br>

`drown->sprite.weed[3][48][20];`  : Seaweed. Animated. Used aplenty. <br>

`drown->sprite.moss[60][60];` : Sea moss/foliage. Not necessarily animated. Used aplenty. <br>

`drown->sprite.foliage[128][128];`  : Some see-through foliage. Necessary for "see-through wall" requirement.

`drown->sprite.goal[6][128][64];` : The dangling rope in the surface. Probably needs to be quite visible and animated.

`drown->sprite.left_arm[?][?][?];`  : Overlay. Player's left arm. The weapon. More frames than left arm due to weapon animation. <br>

`drown->sprite.ammo[3][12][12];`  : Overlay HUD. Remaining ammo in weapon. Probably animated. <br>

`drown->sprite.timer[?][20][20];` : Overlay HUD. Remaining time. Most definitely animated. <br>

`drown0>storyboard.title_screen[642][480];` : Title splash screen. One or a few frames. <br>

`drown->storyboard.beginning[3][642][480];` : Starting cutscene. Three or four frames. <br>

`drown->storyboard.bad_end[3][642][480];` : Ending cutscene. Three or four frames. Monster wins. <br>

`drown->storyboard.good_end[3][642][480];`  : Ending cutscene. Three or four frames. Player wins. <br>
