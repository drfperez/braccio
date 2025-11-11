const express = require("express");
const http = require("http");
const { Server } = require("socket.io");
const { Board, Servo } = require("johnny-five");

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.use(express.static("."));

const board = new Board();
let s1, s2;

board.on("ready", () => {
  console.log("✅ Arduino Braccio connectat via Johnny-Five!");
  s1 = new Servo(9);
  s2 = new Servo(10);

  io.on("connection", (socket) => {
    console.log("🖥️ Client web connectat");
    socket.emit("status", "Braccio connectat!");

    socket.on("angles", ({ q1, q2 }) => {
      s1.to(q1);
      s2.to(q2);
      socket.emit("feedback", { q1, q2, time: Date.now() });
    });

    socket.on("reprodueixTrajectoria", (seq) => {
      console.log("▶️ Reproduint trajectòria");
      seq.forEach((p, i) => {
        setTimeout(() => {
          s1.to(p.q1);
          s2.to(p.q2);
          socket.emit("feedback", { q1: p.q1, q2: p.q2, time: Date.now() });
        }, i * 200);
      });
    });
  });
});

const PORT = 3000;
server.listen(PORT, () => console.log(`🌐 Servidor actiu a http://localhost:${PORT}`));
