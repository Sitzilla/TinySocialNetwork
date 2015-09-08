# TinySocialNetwork
Homework assignment from Programming Foundations II.  Problem found at:
http://csce.uark.edu/~lbg002/csce2014/homework/homework-5-tiny-social-network/

<h2>I. Problem Statement</h2>
<p>Hash tables are useful for looking up records in a database based on a particular field and for keeping track of &#8220;relationships&#8221; between records. In this assignment, you will implement a social network with three main components:</p>
<ol>
<li>A <code>User</code> class with a name and list of pointers to friends of that <code>User</code>.</li>
<li>A hash table that stores <code>User</code> objects based on name.</li>
<li>A hash table that stores friendship statuses between two <code>Users</code> as <code>booleans</code>.</li>
</ol>
<p>Your program should be a while loop that accepts command line input until the quit command is given, much like in previous assignments. You should allow the following commands:</p>
<table>
<tr>
<th>Command</th>
<th>Description</th>
</tr>
<tr>
<td><code>register [name]</code></td>
<td>Register a new <code>User</code> in the network with the given name. You may assume that no two users will have the same name, and that names do not contain spaces. If the user already exists, this should do nothing.</td>
</tr>
<tr>
<td><code>unregister [name]</code></td>
<td>Unregister a <code>User</code> in the network with the given name. If the user does not exist, this should do nothing.</td>
</tr>
<tr>
<td><code>friend [name1] [name2]</code></td>
<td>Record that <code>User</code> objects with names name1 and name2 are friends. If they were already friends, this should do nothing.</td>
</tr>
<tr>
<td><code>unfriend [name1] [name2]</code></td>
<td>Record that <code>User</code> objects with names name1 and name2 are no longer friends. If they were already not friends, this should do nothing.</td>
</tr>
<tr>
<td><code>list [name]</code></td>
<td>List all friends of the <code>User</code> with the given name.</td>
</tr>
<tr>
<td><code>checkfriends [name1] [name2]</code></td>
<td>Print &#8220;yes&#8221; (or some kind of affirmative) if <code>User</code> objects with names name1 and name2 are friends. Print &#8220;no&#8221; (or some kind of negative) otherwise.</td>
</tr>
<tr>
<td><code>quit</code></td>
<td>Exit the program.</td>
</tr>
</table>
<p>Here is a sample of what your program should do ($ is a prompt for input):</p>
<pre class="ignore:true">
$ register Luke
$ register Rebekah
$ register Elizabeth
$ register Gerry
$ friend Luke Rebekah
$ friend Elizabeth Gerry
$ friend Rebekah Elizabeth
$ list Luke
Luke's Friends List
Rebekah
$ list Rebekah
Rebekah's Friends List
Luke
Elizabeth
$ list Gerry
Gerry's Friends List
Elizabeth
$ checkfriends Gerry Elizabeth
Gerry and Elizabeth are friends
$ checkfriends Luke Gerry
Luke and Gerry are not friends
$ unfriend Rebekah Elizabeth
$ list Rebekah
Rebekah's Friends List
Luke
$ friend Rebekah Elizabeth
$ friend Luke Gerry
$ friend Elizabeth Luke
$ checkfriends Luke Elizabeth
Luke and Elizabeth are friends
$ list Luke
Luke's Friends List
Rebekah
Gerry
Elizabeth
$ unregister Gerry
$ list Elizabeth
Elizabeth's Friends List
Rebekah
Luke
$ list Gerry
Gerry is not a registered user!
$ quit
</pre>
<p>You will receive 20 bonus points for implementing all of the commands. You will receive full credit for implementing all except for <em>either</em> <code>unregister</code> or <code>unfriend</code> (but not for omitting both!). You will not receive full credit if you implement less than 6 of the 7 commands.</p>
