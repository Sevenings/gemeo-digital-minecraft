const socket = new WebSocket('ws://localhost:8080');

socket.onmessage = ({ data }) => {
    console.log('Message from server ', data);
};

document.getElementById('send_button').onclick = () => {
    message = document.getElementById('message_input').value
    console.log(message);
    socket.send(message);
};

