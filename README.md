#DevLog - ~13:45h
Dungeon Game

## Game 6/10 in the 10 games in 10 weeks challenge
////////////////////////////////////
              NOTE:
////////////////////////////////////
#### Goals:
- spend min ~12h per game
- aim for 10 games by week 10 
- have a small scope finished game by the end of the week
- even if not finished - still release it

////////////////////////////////////
              TODO:
////////////////////////////////////

//- mockup
//- room generation
- enemy generation in rooms
- enemy pathfinding
- basic combat
- - player hp
- - enemy hp
- - player deal dmg
- - enemy deal dmg
- - player take dmg
- - enemy take dmg
- player stats
- cleared room rewards


////////////////////////////////////
              DONE:
////////////////////////////////////

//20.11
- room types and states ~0:20
- teleport player in front of door when transitioning to new room -0:10
- fix: going out of corner screen bounds 0:05

//19.11 - 1:30
- connect all neighbours to every room
- fixed transitioning from room to room

//17.11 - 2h
- player move between rooms
- refactoring from yesterday's code

//16.1 - 2:45
- floor generation - 1:30
- player movement basics - 0;45
- setup current room layout to match generated rooms 0:25
- - using debug rects visualise room and state
- player movement limited only to floor bounds - 0:05
- detect which door is connected to another room and only highlight it

//15.11 - 2:30
- WIP floor generation - 2:30h
- - before creating new room, need to check spatially around for neighboors

//14.11 - 3:30
- WIP mockup - 1:30h
- WIP room generation - 2h
- - almost done, need to know which rooms connects with it

//13.11 - ~1h
- WIP mockup
- project skeleton from template
