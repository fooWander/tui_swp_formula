<?php
 include 'core/init.php';
 include 'includes/overall/header.php';
 protect_page();
?>		
<!-- Laden der Daten aus der SQL DB -->
<script src="scripts/fahrdynamik_script.js"></script>

<!-- Contentbereich ANFANG -->
	
	
	
<div class="content">
	<div class="single">

		<div class="fahrdyn_div">
			<div class="top akkubig" id="antrieb">N/A</div>	
			<div class="top akkusmall" >Antriebsschlupfregelung</div>	
		</div>				
		<div class="akku_divline"></div>
		<div class="fahrdyn_div">	
			<div class="top akkubig" id="tvec">N/A</div>	
			<div class="top akkusmall" >Torque Vectoring</div> 
		</div>
		<div class="akku_divline"></div>			
		<div class="fahrdyn_div">
			<div class="top akkubig" id="lenkwinkel">N/A</div>
			<div class="top akkusmall" >Lenkwinkel</div>
		</div>
	</div>
		

</div>
		
	
<?php include 'includes/overall/footer.php';?>