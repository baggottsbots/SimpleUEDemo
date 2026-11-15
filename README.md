# SimpleUEDemo - Unreal Engine 5 Interactive Cube Demo

A minimal C++ Unreal Engine 5 project demonstrating a custom InteractiveCube actor.

## What it does
- InteractiveCube is a basic cube actor.
- Starts red.
- When a Pawn (your player character) overlaps it, it turns green and prints "Cube Collected! Score +1" to the screen.

## How to test / open
1. Clone this repository:
   ```
   git clone https://github.com/baggottsbots/SimpleUEDemo.git
   ```
2. Open `SimpleUEDemo.uproject` with Unreal Engine 5.4 or later (right-click > Open with Unreal Engine, or drag onto UE icon).
3. The editor will detect the C++ module and prompt to compile / generate project files. Allow it (requires Visual Studio with C++ workload on Windows, or Xcode on Mac).
4. Once open:
   - Create a new level or use the default Open World.
   - In Content Browser or Place Actors, search for `InteractiveCube` and place several in the level.
   - Add a Player Start if needed.
   - Hit Play (Alt+P). Walk into the red cubes with your character to collect them (they turn green).

## Notes
- This is a bare-bones project. You may want to start from the Third Person template and migrate the InteractiveCube class if you prefer a ready character.
- No custom GameMode is required; the default works.
- Dynamic materials assume the default engine cube material supports BaseColor parameter. If color doesn't change, create a simple Material with a Vector Parameter named BaseColor and assign it.

Created by Grok team for testing purposes.

## Alternative: Immediate browser test
For a quick test without Unreal Engine installed, see the Three.js version concept below (you can save as index.html and open in any modern browser):

```html
<!DOCTYPE html>
<html>
<head>
  <title>Simple Interactive Cubes (Three.js)</title>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
</head>
<body style="margin:0;">
  <div id="info" style="position:absolute;color:white;padding:10px;">Use WASD to move. Collect red cubes!</div>
  <script>
    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(75, window.innerWidth/window.innerHeight, 0.1, 1000);
    const renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);

    // Simple player (box)
    const playerGeo = new THREE.BoxGeometry(1,1,1);
    const playerMat = new THREE.MeshBasicMaterial({color: 0x0000ff});
    const player = new THREE.Mesh(playerGeo, playerMat);
    scene.add(player);
    camera.position.z = 5;

    // Cubes
    const cubes = [];
    for(let i=0; i<5; i++) {
      const geo = new THREE.BoxGeometry(1,1,1);
      const mat = new THREE.MeshBasicMaterial({color: 0xff0000});
      const cube = new THREE.Mesh(geo, mat);
      cube.position.set((Math.random()-0.5)*20, 0, (Math.random()-0.5)*20);
      scene.add(cube);
      cubes.push(cube);
    }

    const keys = {};
    window.addEventListener('keydown', e => keys[e.key] = true);
    window.addEventListener('keyup', e => keys[e.key] = false);

    function animate() {
      requestAnimationFrame(animate);
      if(keys['w']) player.position.z -= 0.1;
      if(keys['s']) player.position.z += 0.1;
      if(keys['a']) player.position.x -= 0.1;
      if(keys['d']) player.position.x += 0.1;

      // Simple collision
      cubes.forEach(cube => {
        if(cube.material.color.getHex() === 0xff0000 && player.position.distanceTo(cube.position) < 1.5) {
          cube.material.color.set(0x00ff00);
          document.getElementById('info').innerText = 'Collected! Score +1';
        }
      });

      camera.position.x = player.position.x;
      camera.position.z = player.position.z + 5;
      camera.lookAt(player.position);
      renderer.render(scene, camera);
    }
    animate();
  </script>
</body>
</html>
```

Save the above as `index.html` and open it in Chrome/Firefox to test a similar interactive demo instantly.
