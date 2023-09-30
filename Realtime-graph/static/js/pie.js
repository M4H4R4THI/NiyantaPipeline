document.addEventListener('DOMContentLoaded', function () {
    const pieChart = document.getElementById('pieChart').getContext('2d');
    let pieData = [0, 0, 0];

    const chart = new Chart(pieChart, {
        type: 'pie',
        data: {
            labels: ['Low', 'Medium', 'High'],
            datasets: [{
                data: pieData,
                backgroundColor: ['#FF5733', '#F9A602', '#3CFF33']
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            legend: {
                position: 'bottom'
            }
        }
    });

    function updatePieChart() {
        const lowCount = pieData[0];
        const mediumCount = pieData[1];
        const highCount = pieData[2];

        chart.data.datasets[0].data = [lowCount, mediumCount, highCount];
        chart.update();
    }

    function addPieData(flowRate) {
        if (flowRate >= 8) {
            pieData[2]++;
        } else if (flowRate >= 5) {
            pieData[1]++;
        } else {
            pieData[0]++;
        }
        updatePieChart();
    }

    setInterval(function () {

        const randomFlowRate = Math.floor(Math.random() * 10) + 1;
        addPieData(randomFlowRate);
    }, 5000);
});
