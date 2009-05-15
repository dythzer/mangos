Healbot is a patch based on the playerbot patch (many thanks to collinsp, yad, natsukawa and all who worked on it). Many things have been remade and more will. On this patch I focus 100% on only one class (priest), and only healing.
The goal is to make it as intelligent as possible so it can be used as a real healbot and even replace a real healer :)


It lets you summon a priest character from your account as a healbot that you can control and which can aid you and your group.

The healbot will only use abilities that it has learned.

Current GM commands (default GM 2):

.healbot add CHARNAME (add healbot to world)
.healbot remove CHARNAME (logout healbot)

/invite BOTNAME (bot will auto accept invite)

These commands can be used in party chat or whisper:
attack (bot will attack selected target, similar to the way a pet can attack)
follow (orders bot to follow player; will also revive bot if dead or teleport bot if far away)
stay
assist (you'll need to be attacking something and the bot only does melee atm)
spells (replies with all spells known to bot)
cast <SPELLID>
cast <SPELL SUBSTRING>
use <ITEM LINK>
equip <ITEM LINK>
rest (eat or drink if needed)
pws (cast power word: shield on master)

Note: Added botname before command if you have more than one bot spawned and only want to command one of them

If specifying a spell substring, the spell chosen will be in priority of exact name match, highest spell rank, and spell using no reagents. Case does not matter. Here's some examples:
cast greater heal
cast pain
cast poly
cast fort
cast SPELLID


To trade items/money with your bot simply initiate a trade and the bot will tell you how much money and items are available.
To request an item simple whisper the bot and shift click the link of the item you would like. You can link multiple items on the same line.
You can also request money in the following manner when the trade window is open:
10g <-- request that the bot give you 10 gold
6g500s25c <-- request 6 gold, 500 silver, and 25 cooper

The bot will auto-accept trades

To use or equip items for your bot say:
/w equip <ITEMLINK1> <ITEMLINK2>
/w use <ITEMLINK1> <ITEMLINK2>

If you inspect your bot, your bot will tell you what items it has in its inventory that it can equip. To create a link in the chat window, hold the shift key and press the left mouse button when clicking the link.


Use the ScriptName "healbot_giver" if you want an NPC that lets normal players summon healbots.

Known issues:

*The bots don't always face in the right direction.
*Sometimes when a bot makes the kill, the corpse is not lootable.