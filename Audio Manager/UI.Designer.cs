using Sonora;

namespace App;
partial class UI
{
    private System.ComponentModel.IContainer components = null;
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null)) components.Dispose();
        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code
    private void InitializeComponent()
    {
        components = new System.ComponentModel.Container();
        panel1 = new Panel();
        button1 = new Button();
        flowLayoutPanel1 = new FlowLayoutPanel();
        label1 = new Label();
        comboBox1 = new ComboBox();
        contextMenuStrip1 = new ContextMenuStrip(components);
        panel1.SuspendLayout();
        flowLayoutPanel1.SuspendLayout();
        SuspendLayout();
        // 
        // panel1
        // 
        panel1.Controls.Add(button1);
        panel1.Controls.Add(flowLayoutPanel1);
        panel1.Dock = DockStyle.Fill;
        panel1.Location = new Point(0, 0);
        panel1.Name = "panel1";
        panel1.Size = new Size(1325, 639);
        panel1.TabIndex = 0;
        // 
        // button1
        // 
        button1.Location = new Point(12, 61);
        button1.Name = "button1";
        button1.Size = new Size(301, 94);
        button1.TabIndex = 3;
        button1.Text = "button1";
        button1.UseVisualStyleBackColor = true;
        button1.Click += button1_Click_1;
        // 
        // flowLayoutPanel1
        // 
        flowLayoutPanel1.Controls.Add(label1);
        flowLayoutPanel1.Controls.Add(comboBox1);
        flowLayoutPanel1.Location = new Point(12, 12);
        flowLayoutPanel1.Name = "flowLayoutPanel1";
        flowLayoutPanel1.Size = new Size(578, 43);
        flowLayoutPanel1.TabIndex = 2;
        // 
        // label1
        // 
        label1.AutoSize = true;
        label1.Location = new Point(3, 0);
        label1.Name = "label1";
        label1.Size = new Size(123, 25);
        label1.TabIndex = 0;
        label1.Text = "Audio devices";
        label1.Click += label1_Click_3;
        // 
        // comboBox1
        // 
        comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
        comboBox1.Location = new Point(132, 3);
        comboBox1.Name = "comboBox1";
        comboBox1.Size = new Size(429, 33);
        comboBox1.TabIndex = 2;
        comboBox1.SelectionChangeCommitted += ComboBox1_SelectionChangeCommitted;
        // 
        // contextMenuStrip1
        // 
        contextMenuStrip1.ImageScalingSize = new Size(24, 24);
        contextMenuStrip1.Name = "contextMenuStrip1";
        contextMenuStrip1.Size = new Size(61, 4);
        // 
        // Form1
        // 
        AutoScaleDimensions = new SizeF(10F, 25F);
        AutoScaleMode = AutoScaleMode.Font;
        ClientSize = new Size(1325, 639);
        Controls.Add(panel1);
        Name = "Form1";
        Text = "Audio";
        Load += Form1_Load;
        panel1.ResumeLayout(false);
        flowLayoutPanel1.ResumeLayout(false);
        flowLayoutPanel1.PerformLayout();
        ResumeLayout(false);
    }

    #endregion

    private Panel panel1;
    private ContextMenuStrip contextMenuStrip1;
    private FlowLayoutPanel flowLayoutPanel1;
    private Label label1;
    private void DevicesIntoCombo()
    {
        string[] devices = Sonora.SoundWizard.GetDevices();
        if (devices.Length > 0)
        {
            comboBox1.Items.AddRange(devices);
            comboBox1.SelectedIndex = 0;
        }
        else
        {
            comboBox1.Items.Add("No audio devices found");
            comboBox1.SelectedIndex = 0;
            comboBox1.Enabled = false;
        }
    }
    private ComboBox comboBox1;
    private Button button1;
}
