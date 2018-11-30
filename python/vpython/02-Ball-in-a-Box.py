from vpython import *

ball = sphere(pos = vector(-5, 0, 0), radius = 0.5, color = color.cyan, make_trail = True)
wallU = box(pos = vector(0, 6, 0), size=vector(12, 0.2, 12), color = color.green, opacity = 0.1)
wallD = box(pos = vector(0, -6, 0), size=vector(12, 0.2, 12), color = color.green, opacity = 0.1)

wallB = box(pos = vector(0, 0, -6), size=vector(12, 12, 0.2), color = color.green, opacity = 0.1)
wallF = box(pos = vector(0, 0, 6), size=vector(12, 12, 0.2), color = color.green, opacity = 0.1)

wallL = box(pos = vector(-6, 0, 0), size=vector(0.2, 12, 12), color = color.green, opacity = 0.1)
wallR = box(pos = vector(6, 0, 0), size=vector(0.2, 12, 12), color = color.green, opacity = 0.1)
ball.velocity = vector(25, 5, 10)
vscale = 0.1
varr = arrow(pos = ball.pos, axis = vscale * ball.velocity, color = color.yellow)

deltat = 0.005
t = 0

while True:
    rate(100)
    if ball.pos.x >= wallR.pos.x or ball.pos.x <= wallL.pos.x:
        ball.velocity.x = -ball.velocity.x  
    if ball.pos.y >= wallU.pos.y or ball.pos.y <= wallD.pos.y:
        ball.velocity.y = -ball.velocity.y  
    if ball.pos.z >= wallF.pos.z or ball.pos.z <= wallB.pos.z:
        ball.velocity.z = -ball.velocity.z  
    ball.pos = ball.pos + ball.velocity * deltat
    varr.pos = ball.pos
    varr.axis = vscale * ball.velocity
    t += deltat

