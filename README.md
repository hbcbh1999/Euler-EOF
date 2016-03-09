# Euler-EOF

Euler-EOF is a C++ code for solving Euler equation in the inviscous aerodynamic problem. This code is based on a C++ frameworkfor educational purpose provided by Technische Universität München in the course Turbulent Flow Simulation on HPC-Systems in Winter semester 2015.  

## Test case: Slope channel
### Geometry layout 
![alt text](https://raw.githubusercontent.com/muyan93/Euler-EOF/master/supersonic.png "Slope channel")
### Major parameter. 
- Geometry scale

|           | L1  | L2  | L3  | L4   | L5   | H1 |
|-----------|-----|-----|-----|------|------|----|
| Length(m) | 0.1 | 0.2 | 0.4 | 0.28 | 0.42 | 1  | 

Expansion angle delta: 10 degree

- Mesh config

|             | I1 | I2 | I4 | IM  | JM  |
|-------------|----|----|----|-----|-----|
| grid number | 21 | 91 | 61 | 241 | 131 |

- Flow parameter
-- Freestream pressure and temperature: 100kPa,300K
-- Specific heat ratio: 1.4
-- gas constant: 287.05
-- Freestream Mach number: 0.5,0.8,2
