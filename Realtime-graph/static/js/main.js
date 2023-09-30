

const ctx = document.getElementById('myChart');

graphData = {
    type: 'line',
    data: {
        labels: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'June', 'July', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'],
        datasets: [{
        label: '# Sold',
        data: [12, 19, 3, 5, 2, 3, 12, 0, 9, 1, 13, 19],
        fill: true,
        backgroundColor: ['rgba(14, 131, 136, 0.5)'],
        borderColor: ['rgba(14, 131, 136, 1)'],
        borderWidth: 1
        }]
    },
    options: {}
}

var myChart = new Chart(ctx, graphData);

var socket=new WebSocket('ws://localhost:8000/ws/graph/');
socket.onmessage=function(e){
    var djangoData=JSON.parse(e.data)
    var indx=Math.floor(Math.random() * 12)
    graphData.data.datasets[0].data[indx]=djangoData.value
    myChart.update()
    document.getElementById('sold').innerHTML=graphData.data.labels[indx] +": "+ djangoData.value.toString()
}