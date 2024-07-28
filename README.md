<h1>Philosophers</h1>

<h2>Project Overview</h2>
<p>The <code>philosophers</code> project involves learning the basics of threading a process. You will learn how to create threads and discover mutexes through the implementation of the classic "Dining Philosophers" problem.</p>

<h2>Purpose</h2>
<p>The purpose of this project is to write a C program that simulates the dining philosophers problem. The program will create threads for each philosopher and use mutexes to manage access to shared resources (forks).</p>

<h2>What You Will Learn</h2>
<ul>
    <li>How to create and manage threads in C.</li>
    <li>How to use mutexes to protect shared resources and prevent data races.</li>
    <li>How to simulate a concurrent problem with multiple threads.</li>
    <li>How to handle synchronization and avoid deadlocks.</li>
</ul>

<h2>Project Contents</h2>

<h3>Mandatory Part</h3>
<p>You must implement the following requirements:</p>
<ul>
    <li>Write a program named <code>philo</code> that takes the following arguments:
        <ul>
            <li><code>number_of_philosophers</code>: The number of philosophers and also the number of forks.</li>
            <li><code>time_to_die</code> (in milliseconds): If a philosopher doesn’t start eating <code>time_to_die</code> milliseconds after their last meal or the beginning of the simulation, they die.</li>
            <li><code>time_to_eat</code> (in milliseconds): The time it takes for a philosopher to eat. During this time, they will need to hold two forks.</li>
            <li><code>time_to_sleep</code> (in milliseconds): The time a philosopher will spend sleeping.</li>
            <li><code>number_of_times_each_philosopher_must_eat</code> (optional): If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops when a philosopher dies.</li>
        </ul>
    </li>
    <li>Each philosopher is represented by a thread.</li>
    <li>There is one fork between each pair of philosophers. If there is only one philosopher, there is only one fork.</li>
    <li>Use mutexes to protect the state of each fork and prevent data races.</li>
    <li>The program must print a message for each state change of a philosopher formatted as follows:
        <ul>
            <li><code>timestamp_in_ms X has taken a fork</code></li>
            <li><code>timestamp_in_ms X is eating</code></li>
            <li><code>timestamp_in_ms X is sleeping</code></li>
            <li><code>timestamp_in_ms X is thinking</code></li>
            <li><code>timestamp_in_ms X died</code></li>
        </ul>
        Replace <code>timestamp_in_ms</code> with the current timestamp in milliseconds and <code>X</code> with the philosopher number.
    </li>
    <li>The simulation stops when a philosopher dies or if all philosophers have eaten the specified number of times.</li>
</ul>

<h3>Bonus Part</h3>
<p>The bonus part includes additional features:</p>
<ul>
    <li>Write a program named <code>philo_bonus</code> that meets the same requirements as the mandatory part but with the following changes:
        <ul>
            <li>All forks are placed in the middle of the table and represented by a semaphore.</li>
            <li>Each philosopher is represented by a process instead of a thread.</li>
            <li>The main process should not be a philosopher.</li>
        </ul>
    </li>
</ul>
<p>The bonus part will only be assessed if the mandatory part is perfect.</p>

<h2>Usage</h2>
<p>To use the <code>philo</code> program, compile it using the provided Makefile and run it with the appropriate arguments. The program will simulate the dining philosophers problem and print the state changes of each philosopher.</p>

<h2>Conclusion</h2>
<p>The <code>philosophers</code> project provides an opportunity to learn about threading, mutexes, and concurrency in C. By completing this project, you will gain valuable skills in managing concurrent processes and preventing synchronization issues.</p>
