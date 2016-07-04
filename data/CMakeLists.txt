set(DATA_FILES
    player.png
    enemy.png
    bullet.png
    dvu_sans.ttf
    pop.wav
)
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_BINARY_DIR})