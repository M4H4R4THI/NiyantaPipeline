document.addEventListener('DOMContentLoaded', function () {
    const flowRateSelect = document.getElementById('flowRateSelect');
    const submitButton = document.getElementById('submitButton');
    const graph = document.getElementById('graph');
    const regressionResult = document.getElementById('regressionResult');

    const dataPoints = [];
    const checkpoints = {
        initial: { x: null, y: null },
        medium: { x: null, y: null },
        high: { x: null, y: null },
        low: { x: null, y: 0 }
    };


    const ctx = graph.getContext('2d');
    const chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: 'Flow Rate (liters/sec)',
                data: dataPoints,
                borderColor: 'blue',
                borderWidth: 2,
                fill: false
            }]
        },
        options: {
            scales: {
                x: {
                    type: 'linear',
                    position: 'bottom'
                },
                y: {
                    beginAtZero: true,
                    ticks: {
                        callback: function (value, index, values) {
                            if (value === 0) {
                                return 'Low';
                            } else if (value === 5) {
                                return 'Medium';
                            } else if (value === 10) {
                                return 'High';
                            } else {
                                return value;
                            }
                        }
                    }
                }
            }
        }
    });

    function calculateLinearRegression(x, y) {
        const n = x.length;
        let sumX = 0;
        let sumY = 0;
        let sumXY = 0;
        let sumXX = 0;

        for (let i = 0; i < n; i++) {
            sumX += x[i];
            sumY += y[i];
            sumXY += x[i] * y[i];
            sumXX += x[i] * x[i];
        }

        const slope = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);
        const intercept = (sumY - slope * sumX) / n;

        return { slope, intercept };
    }

    submitButton.addEventListener('click', function () {
        const flowRate = parseFloat(flowRateSelect.value);
        if (!isNaN(flowRate)) {
            const currentTime = new Date().getTime();
            dataPoints.push(flowRate);
            chart.data.labels.push(currentTime);
            chart.update();

            if (dataPoints.length === 1) {
                checkpoints.initial.x = currentTime;
                checkpoints.initial.y = flowRate;
            } else if (dataPoints.length === Math.floor(chart.data.labels.length / 2)) {
                checkpoints.medium.x = currentTime;
                checkpoints.medium.y = flowRate;
            } else if (dataPoints.length === Math.floor(chart.data.labels.length * 3 / 4)) {
                checkpoints.high.x = currentTime;
                checkpoints.high.y = flowRate;
            } else if (dataPoints.length === chart.data.labels.length) {
                checkpoints.low.x = currentTime;
                checkpoints.low.y = 0;
            }

            ctx.clearRect(0, 0, graph.width, graph.height);
            chart.update();
            ctx.strokeStyle = 'red';
            ctx.lineWidth = 2;

            ctx.beginPath();
            ctx.moveTo(checkpoints.initial.x, checkpoints.initial.y);
            ctx.lineTo(checkpoints.medium.x, checkpoints.medium.y);
            ctx.lineTo(checkpoints.high.x, checkpoints.high.y);
            ctx.lineTo(checkpoints.low.x, checkpoints.low.y);
            ctx.stroke();

            const regressionData = calculateLinearRegression(chart.data.labels, dataPoints);
            const slope = regressionData.slope.toFixed(4);
            const intercept = regressionData.intercept.toFixed(4);

            regressionResult.innerHTML = `Regression Line: y = ${slope}x + ${intercept}`;
        }
    });
});
