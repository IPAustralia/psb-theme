<section id="block-block-6">
<div class="container">
<div id="block-block-6">
<ul class="nav nav-tabs">
	<li class="active"><a data-toggle="tab" href="#attorney"><i class="fa fa-user" aria-hidden="true"></i>&nbsp;&nbsp;Find an Attorney</a></li>
	<li><a data-toggle="tab" href="#incorp"><i class="fa fa-building" aria-hidden="true"></i>&nbsp;&nbsp;Find an Incorporated Attorney</a></li>
</ul>
<div class="tab-content">
	<div id="attorney" class="tab-pane fade in active">
		<!--p id="title"><i class="fa fa-user" aria-hidden="true"></i>&nbsp;&nbsp;Find an Attorney</p-->
		<form action="/resources/find-an-attorney" method="get">
			<input type="search" name="field_last_name_value" placeholder="Last name"> 	<input type="search" name="field_address_locality" placeholder="Town/City (optional)"> <input type="submit" value="Search">
		</form> 
		<p>OR <a href="/resources/find-an-attorney">view directory of attorneys</a></p>
	</div>
	<div id="incorp" class="tab-pane fade">
	<!--p id="title"><i class="fa fa-user" aria-hidden="true"></i>&nbsp;&nbsp;Find a firm</p-->
		<form action="/resources/directory-of-firms" method="get">
			<input type="search" name="title" placeholder="Firm name"><input type="submit" value="Search">
		</form> 
		<p>OR <a href="/resources/directory-of-firms">view directory of firms</a></p>
	</div>
</div>
</div>
</div>
<script type="text/javascript">
/*jQuery(function() {
  jQuery('form').submit(function(){
    jQuery.post('http://example.com/upload', $('#form_id').serialize(), function() {
      window.location = 'http://google.com';
    });
    return false;
  });
});*/
</script>
</section>